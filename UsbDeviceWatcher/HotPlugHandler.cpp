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

    cout << "device with id " << deviceId << " has been connected" << endl;

    if (client->isDeviceEnabledOnServer(deviceId)) {
        cout << "device " << deviceId << " is enabled" << endl;
    } else {
        cout << "device " << deviceId << " is disabled" << endl;
    }
}

HotPlugHandler::~HotPlugHandler() {
}

