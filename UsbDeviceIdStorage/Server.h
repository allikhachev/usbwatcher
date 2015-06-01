/* 
 * File:   server.h
 *
 * Created on May 12, 2015, 8:06 PM
 */

#ifndef SERVER_H
#define	SERVER_H

#include <QObject>
#include <QtCore>
#include "Storage.h"
#include <string>

class QTcpServer;

class Server : public QObject {
    Q_OBJECT
public:
    Server(unsigned short port, Storage * storage);
    virtual ~Server();
private slots:
    void sendResponse();
private:
    Storage * storage;
    QTcpServer *tcpServer;
    static const char RESPONSE_DISABLED[];
    static const char RESPONSE_ENABLED[];
    static const char RESPONSE_ADDED[];
    static const char RESPONSE_NOT_ADDED[];
    static const int BUFFER_LEN = 256;
    char readBuffer [BUFFER_LEN];
    /**
     * Checks device existence in the db.
     * @param peer
     * @param deviceId
     * @return 
     */
    string processGetOpertion(string peer, string deviceId);
    /**
     * Adds new deviceId to the db.
     * @param deviceId 
     * @return true - device added; false - other case
     */
    bool processAddOpertion(string deviceId);
};

#endif	/* SERVER_H */