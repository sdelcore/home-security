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
        syslog (LOG_NOTICE, "Devices found.");

        if(!motionHandler->isMotionRunning())
            return 0;

        system(STOP_MOTION.c_str());

        //do this in a new thread or new process so it doesn't block
        backupFiles();
    }
    else
    {
        syslog (LOG_NOTICE, "No devices found");

        if(motionHandler->isMotionRunning())
            return 0;

        system(START_MOTION.c_str());
    }

    return 0;
}

int CameraProcess::backupFiles()
{
    int ret;
    string tar = motionHandler->getTarCommand();

    ret = system(tar.c_str());

    if(ret < 0)
        return ret;

    ret = system(EMPTY_MOTION_COMMAND.c_str());

    if(ret < 0)
        return ret;

    string scp = "scp /home/pi/tar/*tar.gz pi@192.168.0.13:/HDD/media/home-security/*.tar.gz && rm /home/pi/tar/*.tar.gz";
    ret = system(scp.c_str());
    return ret;
}
