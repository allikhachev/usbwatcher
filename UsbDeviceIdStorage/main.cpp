/*
 * File:   main.cpp
 *
 * Created on May 12, 2015, 7:56 PM
 */

#include <QApplication>
#include "QSettings"
#include "QVariant"
#include <string>
#include <iostream>
#include <stdexcept>

#include "Server.h"

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

    try {
        MyApplication app(argc, argv);

        QSettings settings("settings.ini", QSettings::IniFormat);

        string dbHost = settings.value("db_host", "127.0.0.1").toString().toStdString();
        int dbPort = settings.value("db_port", 3306).toInt();
        string dbName = settings.value("db_name", "usbwatcher").toString().toStdString();
        string userName = settings.value("db_user_name", "usbwatcher").toString().toStdString();
        string userPass = settings.value("db_user_pass", "usbwatcher").toString().toStdString();

        unsigned short port = settings.value("server_port", 1061).toInt();

        Storage storage(dbHost, dbPort, dbName, userName, userPass);
        Server server(port, &storage);

        return app.exec();
    } catch (std::runtime_error * err) {
        cout << err->what() << endl;
    }
}
