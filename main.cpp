/*
 * File:   CheckerClient.cpp
 *
 * Created on April 27, 2015, 10:17 PM
 */

#include <iostream>
#include <stdexcept>
#include "HotPlugHandler.h"
#include "UsbWatcher.h" 

int main(int argc, char *argv[]) {
    int classCount = 1;
    int classes[] = {0x08};
    
    UsbWatcher::CLASS_COUNT = classCount;
    UsbWatcher::CLASSES = classes;
    try {
        HotPlugHandler checker;
        UsbWatcher watcher;

        watcher.init();
        watcher.setHotPlugHandler(&checker);

        while (true) {
            watcher.handleEvents();
        }
    } catch (std::runtime_error * err) {
        cout << err->what() << endl;
    }
}