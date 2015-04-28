/* 
 * File:   UsbWatcher.h
 *
 * Created on April 27, 2015, 10:47 PM
 */

#ifndef USBWATCHER_H
#define	USBWATCHER_H

using namespace std;

class UsbWatcher {
public:
    UsbWatcher(int devClasses []);
    void setHotplagHandler(void (* handler)(string deviceId));
    virtual ~UsbWatcher();
private:
    void (* hotplagHandler)();
};

#endif	/* USBWATCHER_H */

