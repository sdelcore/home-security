#ifndef STORAGEPROCESS_H
#define STORAGEPROCESS_H

#include "homesecurity.h"

using namespace std;

class StorageProcess : public HomeSecurity
{
public:
    StorageProcess();
    int process();
};

#endif // STORAGEPROCESS_H
