/* 
 * File:   DeviceChecker.cpp
 * 
 * Created on April 27, 2015, 10:50 PM
 */

#include "HotPlugHandler.h"
#include <iostream>
#include <string>
#include "QMessageBox"
#include "QTextCodec"

using namespace std;

HotPlugHandler::HotPlugHandler(string hostName, unsigned short port) {
    this->client = new Client(hostName, port);
    QTextCodec::setCodecForTr(QTextCodec::codecForName("System"));
}

void HotPlugHandler::performAction(string deviceId) {

    cout << "device with id " << deviceId << " has been connected" << endl;

    string message = "Вы подключили устройство c идентификатором " + deviceId + ". Добавить его?";

    int result = QMessageBox::question(0, trUtf8("Добавлено устройство1"), trUtf8(message.c_str()),
            QMessageBox::Cancel | QMessageBox::Ok, QMessageBox::Ok);

    if (result == QMessageBox::Ok) {
        if (client->addDeviceOnServer(deviceId)) {
            cout << "device with id " << deviceId << " has been added" << endl;
            QMessageBox::information(0, trUtf8("Сообщение"), trUtf8("Устройство успешно добавлено"),
            QMessageBox::Ok, QMessageBox::Ok);
        } else {
            cout << "device with id " << deviceId << " has not been added" << endl;
            QMessageBox::warning(0, trUtf8("Внимание!"), trUtf8("Устройство не было добавлено"),
            QMessageBox::Ok, QMessageBox::Ok);
        }
    }
}

HotPlugHandler::~HotPlugHandler() {
}

