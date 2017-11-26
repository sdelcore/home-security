#ifndef CAMERAPROCESS_H
#define CAMERAPROCESS_H

#include "homesecurity.h"

using namespace std;

class CameraProcess : public HomeSecurity
{
public:
    CameraProcess();
    int process();
    int backupFiles();
};

#endif // CAMERAPROCESS_H
