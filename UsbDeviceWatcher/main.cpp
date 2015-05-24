/*
 * File:   CheckerClient.cpp
 *
 * Created on April 27, 2015, 10:17 PM
 */

#include "QApplication"
#include "QSettings"
#include "QVariant"
#include "QObject"
#include "QTimer"
#include "QMessageBox"
#include <iostream>
#include <string>
#include <stdexcept>
#include "HotPlugHandler.h"
#include "UsbWatcher.h"
#include "WarningForm.h"

using namespace std;

int main(int argc, char *argv[]) {
    int classCount = 1;
    int classes[] = {0x08};

    QApplication app(argc, argv);
    QSettings settings("settings.ini", QSettings::IniFormat);

    string host = settings.value("server_host", "127.0.0.1").toString().toStdString();
    unsigned short port = settings.value("server_port", 1061).toInt();

    UsbWatcher::CLASS_COUNT = classCount;
    UsbWatcher::CLASSES = classes;
    try {
        HotPlugHandler handler(host, port);
        UsbWatcher watcher;
        QTimer timer(&app);
        WarningForm form;

        QObject::connect(&watcher, SIGNAL(deviceConnected(string)), &handler, SLOT(performAction(string)));
        QObject::connect(&timer, SIGNAL(timeout()), &watcher, SLOT(handleEvents()));
        QObject::connect(&handler, SIGNAL(deviceDisabled(string)), &form, SLOT(showWarning(string)));
        
        watcher.start();
        timer.start(5000); // handle usb events every 5 sec.
        return app.exec();
    } catch (std::runtime_error * err) {
        cout << err->what() << endl;
    }
}