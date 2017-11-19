#ifndef HOMESECURITY_H
#define HOMESECURITY_H

#include <sys/types.h>
#include <sys/stat.h>
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <errno.h>
#include <unistd.h>
#include <syslog.h>
#include <string.h>

#include "devicehandler.h"
#include "motionhandler.h"

using namespace std;
static const char* DAEMON_NAME = "homesecurityd";

class HomeSecurity
{
private:
    DeviceHandler* deviceHandler;
    MotionHandler* motionHandler;

    string getTimeDateString();
    string getTarCommand();
public:
    HomeSecurity();
    ~HomeSecurity();
    int startDaemon();
    void process();
    int backupFiles();
};

#endif // HOMESECURITY_H
