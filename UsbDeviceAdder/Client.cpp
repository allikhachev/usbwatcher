/* 
 * File:   client.cpp
 * 
 * Created on May 15, 2015, 8:49 PM
 */

#include "QTcpSocket"
#include "Client.h"
#include <iostream>

Client::Client(string hostName, unsigned short port) {
    this->port = port;
    this->hostName = hostName.c_str();
}

bool Client::addDeviceOnServer(string deviceId) {

    const int Timeout = 10 * 1000;

    QTcpSocket socket;
    socket.connectToHost(hostName, port);

    if (!socket.waitForConnected(Timeout)) {
        emit deviceNotAdded(deviceId);
        return false;
    }
    
    string messageToServer = "ADD " + deviceId;

    socket.write(messageToServer.c_str());

    if (!socket.waitForReadyRead(Timeout)) {
        emit deviceNotAdded(deviceId);
        return false;
    }

    socket.readLine(readBuffer, BUFFER_LEN);
    string response(readBuffer);

    if (response.compare("ADDED") == 0) {
        emit deviceAdded(deviceId);
        return true;
    }

    emit deviceNotAdded(deviceId);
    return false;
}

Client::~Client() {
}

