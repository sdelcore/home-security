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

    pid_t pid, sid;

    //create another process to handle taring and sending files
    pid = fork();

    if (pid < 0)
        exit(EXIT_FAILURE);

    //We got a good pid, Close the Parent Process
    if (pid > 0)
        exit(EXIT_SUCCESS);

    //Change File Mask
    umask(0);

    //Create a new Signature Id for our child
    sid = setsid();
    if (sid < 0)
        exit(EXIT_FAILURE);

    syslog (LOG_NOTICE, "started backup");

    int ret;
    string tar = motionHandler->getTarCommand();

    ret = system(tar.c_str());

    if(ret < 0)
        return ret;

    ret = system(EMPTY_MOTION_COMMAND.c_str());

    if(ret < 0)
        return ret;

    string scp = "scp /home/pi/tar/*tar.gz pi@192.168.0.13:" + STORAGE_DIR + "*" + TAR_EXT + " && rm /home/pi/tar/*.tar.gz";
    ret = system(scp.c_str());
    return ret;
}
