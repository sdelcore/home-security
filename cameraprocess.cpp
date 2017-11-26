#include "cameraprocess.h"

CameraProcess::CameraProcess() : HomeSecurity()
{

}

//todo: return something usefull
int CameraProcess::process()
{
    syslog (LOG_NOTICE, "Scanning for devices.");

    bool deviceFound;

    for(int i = 0; i < 3; i++)
    {
        deviceFound = deviceHandler->scanForDevices();

        if(deviceFound)
            break;
    }

    if(deviceFound)
    {
        if(!motionHandler->isMotionRunning())
            return 0;

        syslog (LOG_NOTICE, "Devices found.");

        system(STOP_MOTION.c_str());

        //do this in a new thread or new process so it doesn't block
        backupFiles();
    }
    else
    {
        if(motionHandler->isMotionRunning())
            return 0;

        syslog (LOG_NOTICE, "No devices found");

        system(START_MOTION.c_str());
    }

    return 0;
}

int CameraProcess::backupFiles()
{
    syslog (LOG_NOTICE, "Starting backup");

    int ret;
    string tar = motionHandler->getTarCommand();

    ret = system(tar.c_str());

    if(ret != 0)
        return ret;

    ret = system(EMPTY_MOTION_COMMAND.c_str());

    if(ret != 0)
        return ret;

    string scp = "scp " + HOME_DIR + "tar/*tar.gz " + STORAGE_IP + STORAGE_DIR;

    ret = system(scp.c_str());

    system("rm /home/pi/tar/*.tar.gz");

    return ret;
}
