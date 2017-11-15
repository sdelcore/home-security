#ifndef DEVICEHANDLER_H
#define DEVICEHANDLER_H

#include <iostream>
#include <string>
#include <fstream>

#include "ping.h"

class DeviceHandler
{
public:
    DeviceHandler();
    int performScanCommand(const string& file);
    bool checkForDeviceInFile(const string& file, const string& device);
    bool scanForDevices();
};

#endif // DEVICEHANDLER_H
