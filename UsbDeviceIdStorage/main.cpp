/*
 * File:   main.cpp
 *
 * Created on May 12, 2015, 7:56 PM
 */

#include <QApplication>
//#include <QtCore>
#include <iostream>
#include <stdexcept>

#include "server.h"

using namespace std;

int main(int argc, char *argv[]) {
    // initialize resources, if needed
    // Q_INIT_RESOURCE(resfile);
    try {
        QApplication app(argc, argv);

        Server server(1061);

        //     server.

        return app.exec();
    } catch (std::runtime_error * err) {
        cout << err->what() << endl;
    }
}
