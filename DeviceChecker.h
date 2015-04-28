/* 
 * File:   DeviceChecker.h
 *
 * Created on April 27, 2015, 10:50 PM
 */

#ifndef DEVICECHECKER_H
#define	DEVICECHECKER_H

using namespace std;

class DeviceChecker {
public:
    DeviceChecker();
    /**
     * Checks devise by deviceId
     * @param deviceId contains vendorId and deviceId in format "vendorId:deviceId"
     * @return true - device is enabled, false - other case
     */
    bool isDeviceEnabled(string deviceId);
    virtual ~DeviceChecker();
private:

};

#endif	/* DEVICECHECKER_H */

