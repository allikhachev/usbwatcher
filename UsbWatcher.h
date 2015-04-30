/* 
 * File:   UsbWatcher.h
 *
 * Created on April 27, 2015, 10:47 PM
 */

#ifndef USBWATCHER_H
#define	USBWATCHER_H

#include <libusb-1.0/libusb.h>
#include "DeviceChecker.h"

using namespace std;

class UsbWatcher {
public:
    static int *CLASSES;
    static int CLASS_COUNT;

    UsbWatcher();
    /**
     * Configures libusb and add hotplug listener.
     */
    void init();
    /**
     * Processes events on usb bus.
     */
    void handleEvents();
    /**
     * Adds some action on usb hotplug event.
     * @param handler
     */
    void setDeviceChecker(DeviceChecker * deviceChecker);
    virtual ~UsbWatcher();
private:
    static DeviceChecker * deviceChecker;
    /**
     * Processes libusb hotplug event.
     * @param ctx
     * @param dev
     * @param event
     * @param user_data
     * @return 
     */
    static int LIBUSB_CALL hotplug_callback(libusb_context *ctx, libusb_device *dev,
            libusb_hotplug_event event, void *user_data);
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

