/*
 * File:   CheckerClient.cpp
 *
 * Created on April 27, 2015, 10:17 PM
 */

#include <QApplication>
#include "DeviceChecker.h"
#include "UsbWatcher.h" 

DeviceChecker checker;

static void hotplug_callback(string deviceId) {

    printf("Device %s has been connected\n", deviceId);

}

int main(int argc, char *argv[]) {
    QCoreApplication app(argc, argv);    
    UsbWatcher watcher;

    watcher.setHotplagHandler(hotplug_callback);

    return app.exec();
}
