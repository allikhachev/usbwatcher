/*
 * File:   CheckerClient.cpp
 *
 * Created on April 27, 2015, 10:17 PM
 */

#include "QSettings"
#include "QVariant"
#include <iostream>
#include <string>
#include <stdexcept>
#include "HotPlugHandler.h"
#include "UsbWatcher.h" 

using namespace std;

int main(int argc, char *argv[]) {
    int classCount = 1;
    int classes[] = {0x08};
    
    QSettings settings("settings.ini", QSettings::IniFormat);
    
    string host = settings.value("server_host", "127.0.0.1").toString().toStdString();
    unsigned short port = settings.value("server_port", 1061).toInt();

    UsbWatcher::CLASS_COUNT = classCount;
    UsbWatcher::CLASSES = classes;
    try {
        HotPlugHandler handler(host, port);
        UsbWatcher watcher;

        watcher.init();
        watcher.setHotPlugHandler(&handler);

        while (true) {
            watcher.handleEvents();
        }
    } catch (std::runtime_error * err) {
        cout << err->what() << endl;
    }
}