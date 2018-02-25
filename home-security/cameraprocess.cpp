#include "cameraprocess.h"

CameraProcess::CameraProcess(int argc, char *argv[]) : HomeSecurity()
{
    application = new QCoreApplication(argc, argv);
}

CameraProcess::~CameraProcess()
{
    delete application;
}

int CameraProcess::process(int waitTime)
{
    Q_UNUSED(waitTime);
    bool debug = true;

    WebSocketServer *server = new WebSocketServer(PORT, debug);

    QObject::connect(server, &WebSocketServer::closed, application, &QCoreApplication::quit);
    QObject::connect(server, &WebSocketServer::messageReceived, this, &CameraProcess::onMessageRecieved);

    QTimer timer(this);
    timer.setInterval(waitTime);

    QObject::connect(&timer, &QTimer::timeout, this, &CameraProcess::onTimeout);

    //timer.start();
    return application->exec();
}

void CameraProcess::onTimeout()
{

}

void CameraProcess::onMessageRecieved(QString message)
{
    if(!NFC_TAGS.contains(message))
        return;

    armed = !armed;

    security(armed);
}

int CameraProcess::security(bool start)
{
    if(start)
    {
        if(!motionHandler->isMotionRunning())
            return 0;

        system(STOP_MOTION.c_str());
        backupFiles();
    }
    else
    {
        if(motionHandler->isMotionRunning())
            return 0;

        system(START_MOTION.c_str());
    }

    return 0;
}

int CameraProcess::devicesPresent()
{
    bool deviceFound = false;

    for(int i = 0; i < 3; i++)
    {
        deviceFound = deviceHandler->scanForDevices();

        if(deviceFound)
            break;
    }

    security(deviceFound);

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
