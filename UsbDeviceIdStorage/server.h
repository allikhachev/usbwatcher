/* 
 * File:   server.h
 *
 * Created on May 12, 2015, 8:06 PM
 */

#ifndef SERVER_H
#define	SERVER_H

#include <QObject>
#include <QtCore>

class QTcpServer;

class Server : public QObject {
    Q_OBJECT
public:
    Server(unsigned short port);
    virtual ~Server();
private slots:
    void sendResponse();
private:
    QTcpServer *tcpServer;
    static const char RESPONSE_DISABLED[];
    static const char RESPONSE_ENABLED[];
    static const int BUFFER_LEN = 256;
    char readBuffer [BUFFER_LEN];
};

#endif	/* SERVER_H */