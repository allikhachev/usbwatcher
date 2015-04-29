/*
 * File:   CheckerClient.cpp
 *
 * Created on April 27, 2015, 10:17 PM
 */

#include <iostream>
#include <stdexcept>
#include "DeviceChecker.h"
#include "UsbWatcher.h" 

DeviceChecker checker;

static void hotplug_callback(string deviceId) {

    cout << "Device " << deviceId << " has been connected" << endl;

}

int main(int argc, char *argv[]) {
    try {
        UsbWatcher watcher(NULL);

        watcher.init();
        watcher.setHotplagHandler(hotplug_callback);

        while (true) {
            watcher.handleEvents();
        }
    } catch (std::runtime_error * err) {
        cout << err->what() << endl;
    }
}