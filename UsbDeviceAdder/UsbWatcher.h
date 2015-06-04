/* 
 * File:   UsbWatcher.h
 *
 * Created on April 27, 2015, 10:47 PM
 */

#ifndef USBWATCHER_H
#define	USBWATCHER_H

#include <libusb-1.0/libusb.h>
#include "QObject"
#include <vector>

using namespace std;

class UsbWatcher : public QObject {
    Q_OBJECT
public:
    static int *CLASSES;
    static int CLASS_COUNT;

    UsbWatcher();
    /**
     * Configures libusb and add hotplug listener.
     */
    void start();
    virtual ~UsbWatcher();

signals:
    void deviceConnected(string deviceId);
public slots:
    /**
     * Processes events on usb bus.
     */
    void handleEvents();
private:
    /**
     * list of connected devices.
     */
    vector<string> devices;
    
    /**
     * Compares device class with tested device classes.
     * @param deviceClass 
     * @return ture - device class should be checked, false - otherwise
     */
    static bool isCheckedDeviceClass(libusb_device* dev);
    static bool isCheckedDeviceClass(int deviceClass);
    static string getDeviceId(libusb_device* dev);
    /**
     * Lists connected devices and call deviceChecker for each one.
     */
    void checkConnectedDevices();
};

#endif	/* USBWATCHER_H */

