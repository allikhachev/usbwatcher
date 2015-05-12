/* 
 * File:   DeviceChecker.cpp
 * 
 * Created on April 27, 2015, 10:50 PM
 */

#include "HotPlugHandler.h"
#include <iostream>

HotPlugHandler::HotPlugHandler() {
}

void HotPlugHandler::performAction(string deviceId) {
    cout << "Device " << deviceId << " has been connected" << endl;
}

HotPlugHandler::~HotPlugHandler() {
}

