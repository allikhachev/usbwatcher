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

bool Client::isDeviceEnabledOnServer(string deviceId) {

    const int Timeout = 10 * 1000;

    QTcpSocket socket;
    socket.connectToHost(hostName, port);

    if (!socket.waitForConnected(Timeout)) {
        emit deviceDisabled(deviceId);
        return false;
    }

    socket.write(deviceId.c_str());

    if (!socket.waitForReadyRead(Timeout)) {
        emit deviceDisabled(deviceId);
        return false;
    }

    socket.readLine(readBuffer, BUFFER_LEN);
    string response(readBuffer);

    if (response.compare("ENABLED") == 0) {
        emit deviceEnabled(deviceId);
        return true;
    }

    emit deviceDisabled(deviceId);
    return false;
}

Client::~Client() {
}

