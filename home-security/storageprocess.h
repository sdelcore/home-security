#ifndef STORAGEPROCESS_H
#define STORAGEPROCESS_H

#include "homesecurity.h"

using namespace std;

class StorageProcess : public HomeSecurity
{
public:
    StorageProcess();
    int process(int waitTime = 60000);
    int backup();
};

#endif // STORAGEPROCESS_H
