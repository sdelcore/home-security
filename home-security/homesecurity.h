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
#include <functional>

#include "devicehandler.h"
#include "motionhandler.h"

using namespace std;
static const char* DAEMON_NAME = "homesecurityd";

class HomeSecurity
{
public:
    DeviceHandler* deviceHandler;
    MotionHandler* motionHandler;

    HomeSecurity();
    ~HomeSecurity();
    int startDaemon(int waitTime);
    virtual int process(int waitTime = 60000) = 0;
};

#endif // HOMESECURITY_H
