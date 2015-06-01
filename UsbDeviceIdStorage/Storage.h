/* 
 * File:   storage.h
 *
 * Created on May 17, 2015, 10:34 PM
 */

#ifndef STORAGE_H
#define	STORAGE_H

#include <string>
#include <qt4/QtSql/QSqlDatabase>

using namespace std;

class Storage {
public:
    /**
     * Creates new storage with connection to mysql database.
     * @param hostName
     * @param dbName
     * @param user
     * @param password
     */
    Storage(string hostName, string dbName, string user, string password);
    /**
     * Checks if deviceId is contained in the storage.
     * @param deviceId
     * @return true - storage contains devicsId, false - other case
     */
    bool containsDeviceId(string deviceId);
    /**
     * Adds new deviceId into the storage
     * @param deviceId
     * @return true - deviceId is added, false - other case
     */
    bool addDeviceId(string deviceId);
    
    bool logAccessEvent(string peer, string deviceId);
    
    bool logUnauthorizedAccessEvent(string peer, string deviceId);

    virtual ~Storage();
private:
    QSqlDatabase db;
};

#endif	/* STORAGE_H */

