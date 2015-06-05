/* 
 * File:   storage.cpp
 * 
 * Created on May 17, 2015, 10:34 PM
 */

#include "Storage.h"

#include <stdexcept>
#include <iostream>

#include "QDateTime"
#include "QSqlQuery"
#include "QSqlError"
#include "QString"
#include "QVariant"

Storage::Storage(string hostName, int hostPort, string dbName, string user, string password) {
    db = QSqlDatabase::addDatabase("QMYSQL", "usbwatcher");
    db.setHostName(hostName.c_str());
    db.setPort(hostPort);
    db.setDatabaseName(dbName.c_str());
    db.setUserName(user.c_str());
    db.setPassword(password.c_str());
    bool ok = db.open();
    if (!ok) {
        throw new runtime_error("Cannot create new connection to mysql database");
    }
}

bool Storage::containsDeviceId(string deviceId) {
    QSqlQuery query(db);

    cout << "checking device with id " << deviceId << endl;

    query.prepare("select count(*) from device_id where id = :devId");
    QString value = deviceId.c_str();
    query.bindValue(":devId", value);
    bool ok = query.exec();
    if (!ok) {
        cerr << query.lastError().text().toStdString() << endl;
        return false;
    }

    query.next();
    if (query.value(0).toInt() == 1) {
        cout << "device with id " << deviceId << " has been found" << endl;
        return true;
    }
    cout << "device with id " << deviceId << " has not been found" << endl;
    return false;
}

bool Storage::addDeviceId(string deviceId) {
    QSqlQuery query(db);

    cout << "adding device with id " << deviceId << endl;

    query.prepare("INSERT INTO device_id (id) VALUES (:devId)");
    QString value = deviceId.c_str();
    query.bindValue(":devId", value);
    bool ok = query.exec();
    if (!ok) {
        cerr << query.lastError().text().toStdString() << endl;
        return false;
    }

    return true;
}

bool Storage::logAccessEvent(string peer, string deviceId) {
    QSqlQuery query(db);

    cout << "adding log message for deviceId " << deviceId << endl;

    query.prepare("INSERT INTO access_log (access_time, peer, device_id) VALUES (:time, :peer, :devId)");
    
    query.bindValue(":time", QDateTime::currentDateTime());
    QString peerParam = peer.c_str();
    query.bindValue(":peer", peerParam);
    QString deviceIdParam = deviceId.c_str();
    query.bindValue(":devId", deviceIdParam);
    bool ok = query.exec();
    if (!ok) {
        cerr << query.lastError().text().toStdString() << endl;
        return false;
    }

    return true;
}

bool Storage::logUnauthorizedAccessEvent(string peer, string deviceId) {
    QSqlQuery query(db);

    cout << "adding log message for unauthorized deviceId " << deviceId << endl;

    query.prepare("INSERT INTO unauthorized_access_log (access_time, peer, device_id) VALUES (:time, :peer, :devId)");
    
    query.bindValue(":time", QDateTime::currentDateTime());
    QString peerParam = peer.c_str();
    query.bindValue(":peer", peerParam);
    QString deviceIdParam = deviceId.c_str();
    query.bindValue(":devId", deviceIdParam);
    bool ok = query.exec();
    if (!ok) {
        cerr << query.lastError().text().toStdString() << endl;
        return false;
    }

    return true;
}

Storage::~Storage() {
    db.close();
}

