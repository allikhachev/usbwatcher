/* 
 * File:   UsbWatcher.cpp
 * 
 * Created on April 27, 2015, 10:47 PM
 */

#include <libusb-1.0/libusb.h>
#include <sstream>
#include <iostream>
#include <stdexcept>
#include <iomanip>

#include "UsbWatcher.h"

void (* UsbWatcher::hotplagHandler)(string deviceId);

UsbWatcher::UsbWatcher(int devClasses []) {
    hotplagHandler = NULL;
    
    int rc = libusb_init(NULL);
    if (rc < 0) {
        string error = libusb_error_name(rc);
        error = "failed to initialize libusb: " + error;
        throw new std::runtime_error(error);
    }
}

void UsbWatcher::init() {
    int rc;

    if (!libusb_has_capability(LIBUSB_CAP_HAS_HOTPLUG)) {
        libusb_exit(NULL);
        string error = "Hotplug capabilites are not supported on this platform";
        throw new std::runtime_error(error);
    }

    int vendor_id = LIBUSB_HOTPLUG_MATCH_ANY;
    int product_id = LIBUSB_HOTPLUG_MATCH_ANY;
    int class_id = LIBUSB_HOTPLUG_MATCH_ANY;

    rc = libusb_hotplug_register_callback(NULL, LIBUSB_HOTPLUG_EVENT_DEVICE_ARRIVED, (libusb_hotplug_flag) 0, vendor_id,
            product_id, class_id, hotplug_callback, NULL, NULL);
    if (LIBUSB_SUCCESS != rc) {
        libusb_exit(NULL);
        string error = "Error registering callback 0";
        throw new std::runtime_error(error);
    }
}

void UsbWatcher::handleEvents() {
    int rc = libusb_handle_events(NULL);
    if (LIBUSB_SUCCESS != rc){
        
        string error = libusb_error_name(rc);
        error = "libusb_handle_events() failed: " + error;
        throw new std::runtime_error(error);
    }
}

void UsbWatcher::setHotplagHandler(void(*handler)(string deviceId)) {
    if (handler != NULL) {
        hotplagHandler = handler;
    }
}

int LIBUSB_CALL UsbWatcher::hotplug_callback(libusb_context *ctx, libusb_device *dev, libusb_hotplug_event event, void *user_data) {
    struct libusb_device_descriptor desc;
    int rc;

    rc = libusb_get_device_descriptor(dev, &desc);
    if (LIBUSB_SUCCESS != rc) {
        cerr << "Error getting device descriptor" << endl;
    } else {
        if (hotplagHandler != NULL) {
            stringstream idStream;
            idStream << std::setfill('0') << std::setw(4) << desc.idVendor << ":" << std::setw(4) << desc.idProduct;
            string deviceId(idStream.str());

            hotplagHandler(deviceId);
        }
    }

    return 0;
}

UsbWatcher::~UsbWatcher() {
    libusb_exit(NULL);
}

