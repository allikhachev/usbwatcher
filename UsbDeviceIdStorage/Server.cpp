/* 
 * File:   server.cpp
 * 
 * Created on May 12, 2015, 8:06 PM
 */

#include "Server.h"

#include <stdexcept>
#include <iostream>
#include <sstream>

#include "QTcpServer"
#include "QTcpSocket"

using namespace std;

const char Server::RESPONSE_DISABLED[] = "DISABLED";
const char Server::RESPONSE_ENABLED[] = "ENABLED";
const char Server::RESPONSE_ADDED[] = "ADDED";
const char Server::RESPONSE_NOT_ADDED[] = "NOT ADDED";

Server::Server(unsigned short port, Storage * storage) {
    this->storage = storage;
    if (this->storage == NULL) {
        throw new runtime_error("Storage is not defined");
    }
    tcpServer = new QTcpServer(this);
    if (!tcpServer->listen(QHostAddress::Any, port)) {
        string error = "Unable to start the server: ";
        error = error + tcpServer->errorString().toStdString();
        throw new runtime_error(error);
    }

    //    connect(quitButton, SIGNAL(clicked()), this, SLOT(close()));
    connect(tcpServer, SIGNAL(newConnection()), this, SLOT(sendResponse()));
}

void Server::sendResponse() {
    QTcpSocket *clientConnection = tcpServer->nextPendingConnection();
    connect(clientConnection, SIGNAL(disconnected()), clientConnection, SLOT(deleteLater()));

    stringstream peerStream;
    peerStream << clientConnection->peerAddress().toString().toStdString()
            << ":"
            << clientConnection->peerPort();
    string peer = peerStream.str();

    if (clientConnection->waitForReadyRead(10000)) {
        clientConnection->readLine(readBuffer, BUFFER_LEN);
        string message(readBuffer);
        string deviceId = "";

        if (message.length() > 4) {
            deviceId = message.substr(4);
        }

        if (message.find("GET ", 0, 4) == 0) {
            string response = processGetOpertion(peer, deviceId);
            clientConnection->write(response.c_str());
        } else if (message.find("ADD ", 0, 4) == 0) {
            bool added = processAddOpertion(deviceId);
            if (added) {
                clientConnection->write("ADDED");
            } else {
                clientConnection->write("NOT ADDED");
            }
        }
    }
    clientConnection->disconnectFromHost();
}

string Server::processGetOpertion(string peer, string deviceId) {
    if (storage->containsDeviceId(deviceId)) {
        storage->logAccessEvent(peer, deviceId);
        return RESPONSE_ENABLED;
    } else {
        storage->logUnauthorizedAccessEvent(peer, deviceId);
        return RESPONSE_DISABLED;
    }
}

bool Server::processAddOpertion(string deviceId) {
    if (storage->containsDeviceId(deviceId)) {
        return true;
    } else {
        return storage->addDeviceId(deviceId);
    }
}

Server::~Server() {
    tcpServer->close();
}

