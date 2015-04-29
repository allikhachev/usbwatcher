/* 
 * File:   UsbWatcher.h
 *
 * Created on April 27, 2015, 10:47 PM
 */

#ifndef USBWATCHER_H
#define	USBWATCHER_H

#include <libusb-1.0/libusb.h>

using namespace std;

class UsbWatcher {
public:
    UsbWatcher(int devClasses []);
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
    void setHotplagHandler(void (* handler)(string deviceId));
    
    virtual ~UsbWatcher();
private:
    static void (* hotplagHandler)(string deviceId);
    static int LIBUSB_CALL hotplug_callback(libusb_context *ctx, libusb_device *dev,
            libusb_hotplug_event event, void *user_data);
};

#endif	/* USBWATCHER_H */

