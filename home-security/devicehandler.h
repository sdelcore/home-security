#ifndef DEVICEHANDLER_H
#define DEVICEHANDLER_H

#include <iostream>
#include <string>
#include <fstream>

#include "ping.h"

static const string OUTPUT_FILE = "output";
static const string NMAP_COMMAND = "sudo nmap -sP -oG";
static const string IP_GATEWAY = "192.168.0.0/24";
static const string DEVICES[2] = {"192.168.0.20", "192.168.0.21"};

using namespace std;

class DeviceHandler
{
public:
    DeviceHandler();
    int performScanCommand(const string& file);
    bool checkForDeviceInFile(const string& file, const string& device);
    bool scanForDevices();
};

#endif // DEVICEHANDLER_H
