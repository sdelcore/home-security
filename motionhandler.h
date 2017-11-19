#ifndef MOTIONHANDLER_H
#define MOTIONHANDLER_H

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <dirent.h>
#include <sys/types.h>
#include <iostream>
#include <sys/stat.h>

using namespace std;

static const string MOTION = "motion";
static const string START_MOTION = MOTION + " -b";
static const string STOP_MOTION = "killall " + MOTION;

static const string HOME_DIR = "/home/pi/";
static const string MOTION_DIR = HOME_DIR + "Motion";

static const string TAR_EXT = ".tar.gz";
static const string TAR_COMMAND_START = "tar -zcfv ";
static const string TAR_COMMAND_END = " " + MOTION_DIR;
static const string UNTAR_COMMAND = "tar -zxfv *" + TAR_EXT;

static const string EMPTY_MOTION_COMMAND = "rm -rf " + MOTION_DIR + "/";

class MotionHandler
{
public:
    MotionHandler();
    bool isMotionRunning();
    int folderSize(const char* folder);
private:
    pid_t findProcess(const char* name);
};

#endif // MOTIONHANDLER_H
