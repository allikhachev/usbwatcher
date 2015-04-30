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
#include <string>
#include <qt4/QtCore/qglobal.h>

#include "UsbWatcher.h"

DeviceChecker * UsbWatcher::deviceChecker = NULL;
int classes[] = {0x08};
int *UsbWatcher::CLASSES = classes;
int UsbWatcher::CLASS_COUNT = 1;

UsbWatcher::UsbWatcher() {
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
    if (LIBUSB_SUCCESS != rc) {

        string error = libusb_error_name(rc);
        error = "libusb_handle_events() failed: " + error;
        throw new std::runtime_error(error);
    }
}

void UsbWatcher::setDeviceChecker(DeviceChecker * deviceChecker) {
    if (deviceChecker != NULL) {
        this->deviceChecker = deviceChecker;
        checkConnectedDevices();
    }
}

int LIBUSB_CALL UsbWatcher::hotplug_callback(libusb_context *ctx, libusb_device *dev,
        libusb_hotplug_event event, void *user_data) {

    if (deviceChecker != NULL && isCheckedDeviceClass(dev)) {
        string deviceId = getDeviceId(dev);

        if (!deviceId.empty())
            deviceChecker->isDeviceEnabled(deviceId);
    }

    return 0;
}

string UsbWatcher::getDeviceId(libusb_device* dev) {
    int rc;
    struct libusb_device_descriptor desc;

    rc = libusb_get_device_descriptor(dev, &desc);
    if (LIBUSB_SUCCESS != rc) {
        return string("");
    } else {
        stringstream idStream;
        idStream << std::setfill('0') << std::setw(4) << desc.idVendor << ":" << std::setw(4) << desc.idProduct;
        return string(idStream.str());
    }
}

void UsbWatcher::checkConnectedDevices() {
    libusb_device **list;
    ssize_t cnt = libusb_get_device_list(NULL, &list);

    if (cnt < 0)
        return;
    for (ssize_t i = 0; i < cnt; i++) {
        libusb_device *device = list[i];
        if (deviceChecker != NULL && isCheckedDeviceClass(device)) {
            string deviceId = getDeviceId(device);
            if (!deviceId.empty())
                deviceChecker->isDeviceEnabled(deviceId);
        }
    }

    libusb_free_device_list(list, 1);
};

bool UsbWatcher::isCheckedDeviceClass(int deviceClass) {
    for (int i = 0; i < CLASS_COUNT; i++) {
        if (CLASSES[i] == deviceClass)return true;
    }
    return false;
}

bool UsbWatcher::isCheckedDeviceClass(libusb_device* dev) {
    libusb_device_descriptor desc;
    int rc = libusb_get_device_descriptor(dev, &desc);
    if (LIBUSB_SUCCESS != rc) {
        return false;
    }
    if (0 != (int) desc.bDeviceClass)
        return isCheckedDeviceClass((int) desc.bDeviceClass);

    libusb_config_descriptor *config;
    libusb_get_config_descriptor(dev, 0, &config);

    const libusb_interface *inter;
    const libusb_interface_descriptor *interdesc;
    for (int i = 0; i < (int) config->bNumInterfaces; i++) {
        inter = &config->interface[i];
        for (int j = 0; j < inter->num_altsetting; j++) {
            interdesc = &inter->altsetting[j];
            if (isCheckedDeviceClass((int) interdesc->bInterfaceClass))
                return true;
        }
    }
    return false;
}

UsbWatcher::~UsbWatcher() {
    libusb_exit(NULL);
}

