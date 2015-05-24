/* 
 * File:   client.h
 *
 * Created on May 15, 2015, 8:49 PM
 */

#ifndef CLIENT_H
#define	CLIENT_H

#include <string>
#include "QObject"

using namespace std;

class Client : public QObject {
    Q_OBJECT
public:
    Client(string hostName, unsigned short port);
    virtual ~Client();
    /**
     * Checks device id on server side. 
     * Emits deviceEnabled and deviceDisabled signals.
     * @param deviceId
     * @return true - device Id enabled; device Id disabled
     */
    bool isDeviceEnabledOnServer(string deviceId);
    void run();

signals:
    void deviceEnabled(string deviceId);
    void deviceDisabled(string deviceId);

private:
    QString hostName;
    quint16 port;
    static const int BUFFER_LEN = 256;
    char readBuffer [BUFFER_LEN];
};

#endif	/* CLIENT_H */









