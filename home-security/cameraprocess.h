#ifndef CAMERAPROCESS_H
#define CAMERAPROCESS_H

#include "homesecurity.h"
#include "websocketserver.h"
#include <QtCore/QCoreApplication>
#include <QTimer>

using namespace std;

class CameraProcess : public QObject, public HomeSecurity
{
    Q_OBJECT
public:
    CameraProcess(int argc, char *argv[]);
    ~CameraProcess();
    int process(int waitTime = 60000);

private Q_SLOTS:
    void onMessageRecieved(QString message);
    void onTimeout();

private:
    QCoreApplication* application;
    bool armed = false;
    const int PORT = 8080;
    const QStringList NFC_TAGS = { "82DDFDE", "884DFDE" };
    int security(bool start);
    int devicesPresent();
    int backupFiles();
};

#endif // CAMERAPROCESS_H
