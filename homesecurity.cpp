#include "homesecurity.h"

HomeSecurity::HomeSecurity()
{
    deviceHandler = new DeviceHandler();
    motionHandler = new MotionHandler();
}

HomeSecurity::~HomeSecurity()
{
    //make sure motion is stopped
    if(motionHandler->isMotionRunning())
        system(STOP_MOTION.c_str());
    delete deviceHandler;
    delete motionHandler;
}

int HomeSecurity::startDaemon()
{
    //Set our Logging Mask and open the Log
    setlogmask(LOG_UPTO(LOG_NOTICE));
    openlog(DAEMON_NAME, LOG_CONS | LOG_NDELAY | LOG_PERROR | LOG_PID, LOG_USER);

    syslog(LOG_INFO, "Entering Daemon");

    pid_t pid, sid;

    //Fork the Parent Process, pid = 0 is child
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

    //Change Directory
    //If we cant find the directory we exit with failure.
    if ((chdir("/")) < 0)
        exit(EXIT_FAILURE);
    //Close Standard File Descriptors
    close(STDIN_FILENO);
    close(STDOUT_FILENO);
    close(STDERR_FILENO);

    //----------------
    //Main Process
    //----------------
    while(true){
        process();
        sleep(30);
    }

    //Close the log
    closelog ();
}

//todo: return something usefull
void HomeSecurity::process()
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
            return;

        system(STOP_MOTION.c_str());
    }
    else
    {
        syslog (LOG_NOTICE, "No devices found");

        if(motionHandler->isMotionRunning())
            return;

        system(START_MOTION.c_str());
    }
}

int HomeSecurity::backupFiles()
{
    int ret;
    string tar = getTarCommand();
    /*
    //ret = system(tar);

    if(ret < 0)
        return ret;
    */

    //for now just upload them all without taring them
    string scp = "scp /home/pi/Motion pi@192.168.0.13:/home/pi/Motion && rm /home/pi/Motion/*";
    ret = system(scp.c_str());
    return ret;
}

string HomeSecurity::getTarCommand()
{
    return TAR_COMMAND_START + getTimeDateString() + TAR_COMMAND_END;
}

string HomeSecurity::getTimeDateString()
{
    time_t rawtime;
    tm* timeinfo;
    char buffer [80];

    time(&rawtime);
    timeinfo = localtime(&rawtime);

    strftime(buffer,80,"%Y-%m-%d-%H-%M-%S",timeinfo);

    return string(buffer, 80);
}
