/* 
 * File:   DeviceChecker.h
 *
 * Created on April 27, 2015, 10:50 PM
 */

#ifndef HOT_PLUG_HANDLER_H
#define	HOT_PLUG_HANDLER_H

#include <string>
#include "Client.h"

using namespace std;

/**
 * Performs some operation when a Usb device is connected.
 */
class HotPlugHandler {
public:
    HotPlugHandler(string hostName, unsigned short port);
    /**
     * Performs some operation with usb devise; deviceId is used.
     * @param deviceId contains vendorId and deviceId in format "vendorId:deviceId"
     * @return true - device is enabled, false - other case
     */
    void performAction(string deviceId);
    virtual ~HotPlugHandler();
private:
    Client * client;

};

#endif	/* HOT_PLUG_HANDLER_H */

