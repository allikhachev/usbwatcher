/* 
 * File:   DeviceChecker.cpp
 * 
 * Created on April 27, 2015, 10:50 PM
 */

#include "DeviceChecker.h"
#include <iostream>

DeviceChecker::DeviceChecker() {
}

bool DeviceChecker::isDeviceEnabled(string deviceId) {
    cout << "Device " << deviceId << " has been connected" << endl;
    return false; // TODO: stub
}

DeviceChecker::~DeviceChecker() {
}

