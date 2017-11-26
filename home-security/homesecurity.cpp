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

int HomeSecurity::startDaemon(int waitTime)
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

    int processReturn;
    //----------------
    //Main Process
    //----------------
    while(true){
        processReturn = process();

        if(processReturn < 0)
            break;

        sleep(waitTime);
    }

    //Close the log
    closelog ();
    return 0;
}
