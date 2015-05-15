/* 
 * File:   server.cpp
 * 
 * Created on May 12, 2015, 8:06 PM
 */

#include <stdexcept>
#include <string>
#include <iostream>
#include "qt4/QtNetwork/QTcpServer"
#include "qt4/QtNetwork/QTcpSocket"
#include "server.h"

using namespace std;

const char Server::RESPONSE_DISABLED[] = "DISABLED";
const char Server::RESPONSE_ENABLED[] = "ENABLED";

Server::Server(unsigned short port) {
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

    if (clientConnection->waitForReadyRead(10000)) {
        clientConnection->readLine(readBuffer, BUFFER_LEN);
        cout << readBuffer << endl;
        
        //TODO add usb device checking 
    }

    clientConnection->write(RESPONSE_ENABLED);
    clientConnection->disconnectFromHost();
}

Server::~Server() {
    tcpServer->close();
}

