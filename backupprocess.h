#ifndef BACKUPPROCESS_H
#define BACKUPPROCESS_H

#include "homesecurity.h"

using namespace std;

class BackupProcess : public HomeSecurity
{
public:
    BackupProcess();
    int process();
};

#endif // BACKUPPROCESS_H
