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
#include <algorithm>

#include "UsbWatcher.h"

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

void UsbWatcher::start() {
    checkConnectedDevices();
}

void UsbWatcher::handleEvents() {
    checkConnectedDevices();
}

string UsbWatcher::getDeviceId(libusb_device* dev) {
    int rc;
    struct libusb_device_descriptor desc;

    rc = libusb_get_device_descriptor(dev, &desc);
    if (LIBUSB_SUCCESS != rc) {
        return string("");
    } else {
        stringstream idStream;
        idStream << std::setfill('0') << std::hex
                << std::setw(4) << desc.idVendor << ":"
                << std::setw(4) << desc.idProduct;
        return string(idStream.str());
    }
}

void UsbWatcher::checkConnectedDevices() {
    libusb_device **list;
    ssize_t cnt = libusb_get_device_list(NULL, &list);
    
    vector<string> newDevices;

    if (cnt < 0)
        return;
    for (ssize_t i = 0; i < cnt; i++) {
        libusb_device *device = list[i];
        if (isCheckedDevice(device)) {
            string deviceId = getDeviceId(device);
            if (!deviceId.empty())
                newDevices.push_back(deviceId);
            if (find(devices.begin(), devices.end(), deviceId) == devices.end()) {
                emit deviceConnected(deviceId);
            }
        }
    }

    devices = newDevices;

    libusb_free_device_list(list, 1);
};

bool UsbWatcher::isCheckedDeviceClass(int deviceClass) {
    for (int i = 0; i < CLASS_COUNT; i++) {
        if (CLASSES[i] == deviceClass)return true;
    }
    return false;
}

bool UsbWatcher::isCheckedDevice(libusb_device* dev) {
    libusb_device_descriptor desc;
    int rc = libusb_get_device_descriptor(dev, &desc);
    if (LIBUSB_SUCCESS != rc) {
        cerr << "libusb_get_device_descriptor return " << rc << endl;
        return false;
    }
    if (0 != (int) desc.bDeviceClass)
        return isCheckedDeviceClass((int) desc.bDeviceClass);

    libusb_config_descriptor *config;
    libusb_get_config_descriptor(dev, 0, &config);
    rc = libusb_get_config_descriptor(dev, 0, &config);
    if (LIBUSB_SUCCESS != rc) {
        cerr << "libusb_get_config_descriptor return " << rc << endl;
        return false;
    }

    const libusb_interface *inter;
    const libusb_interface_descriptor *interdesc;
    for (int i = 0; i < (int) config->bNumInterfaces; i++) {
        inter = &config->interface[i];
        if ((int) inter->num_altsetting <= 10 && (int) inter->num_altsetting > 0)
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

