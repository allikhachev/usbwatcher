/* 
 * File:   DeviceChecker.cpp
 * 
 * Created on April 27, 2015, 10:50 PM
 */

#include "HotPlugHandler.h"
#include <iostream>

HotPlugHandler::HotPlugHandler(string hostName, unsigned short port) {
    this->client = new Client(hostName, port);
}

void HotPlugHandler::performAction(string deviceId) {
    if (client->isDeviceEnabledOnServer(deviceId)) {
        cout << "Device " << deviceId << " is enabled" << endl;
    } else {
        cout << "Device " << deviceId << " is disabled" << endl;
    }
}

HotPlugHandler::~HotPlugHandler() {
}

