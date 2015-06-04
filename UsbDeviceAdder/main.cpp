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
#include <iostream>
#include <string>
#include <stdexcept>
#include "HotPlugHandler.h"
#include "UsbWatcher.h"

using namespace std;

class MyApplication : public QApplication {
public:

    MyApplication(int& argc, char** argv, int flags = ApplicationFlags) : QApplication(argc, argv, flags){};

    bool notify(QObject* receiver, QEvent* event) {
        try {
            return QApplication::notify(receiver, event);
        } catch (std::exception* err) {
            cout << err->what() << endl;
            return false;
        }
    };
};

int main(int argc, char *argv[]) {
    int classCount = 1;
    int classes[] = {0x08};

    MyApplication app(argc, argv);
    app.setQuitOnLastWindowClosed(false);
    
    QSettings settings("settings.ini", QSettings::IniFormat);

    string host = settings.value("server_host", "127.0.0.1").toString().toStdString();
    unsigned short port = settings.value("server_port", 1061).toInt();

    UsbWatcher::CLASS_COUNT = classCount;
    UsbWatcher::CLASSES = classes;
    try {
        HotPlugHandler handler(host, port);
        UsbWatcher watcher;
        QTimer timer(&app);

        QObject::connect(&watcher, SIGNAL(deviceConnected(string)), &handler, SLOT(performAction(string)));
        QObject::connect(&timer, SIGNAL(timeout()), &watcher, SLOT(handleEvents()));
        
        watcher.start();
        timer.start(2000); // handle usb events every 2 sec.
        return app.exec();
    } catch (std::runtime_error * err) {
        cout << err->what() << endl;
    }
}