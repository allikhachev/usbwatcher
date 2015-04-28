/* 
 * File:   UsbWatcher.cpp
 * 
 * Created on April 27, 2015, 10:47 PM
 */

#include <libusb-1.0/libusb.h>
#include <sstream>

#include "UsbWatcher.h"

UsbWatcher::UsbWatcher() {
    hotplagHandler = NULL;
}

void UsbWatcher::setHotplagHandler(void(*handler)()) {
    if (handler != NULL) {
        hotplagHandler = handler;
    }
}

static int LIBUSB_CALL hotplug_callback(libusb_context *ctx, libusb_device *dev, libusb_hotplug_event event, void *user_data) {
    struct libusb_device_descriptor desc;
    int rc;

    rc = libusb_get_device_descriptor(dev, &desc);
    if (LIBUSB_SUCCESS != rc) {
        fprintf(stderr, "Error getting device descriptor\n");
    } else {
        stringstream idStream;
        idStream << std::setfill('0') << std::setw(4) << desc.idVendor << " : " << std::setw(4) << desc.idProduct;
        string deviceId(idStream.str());

    }

    return 0;
}

UsbWatcher::~UsbWatcher() {
}

