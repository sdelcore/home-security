#include "storageprocess.h"

StorageProcess::StorageProcess() : HomeSecurity()
{

}

int StorageProcess::process(int waitTime)
{
    int processReturn;

    while(true)
    {
        processReturn = backup();

        if(processReturn < 0)
            break;

        sleep(waitTime);
    }
}


int StorageProcess::backup()
{
    if(motionHandler->folderSize(STORAGE_DIR.c_str()) <= 0)
        return 0;

    system(UNTAR_COMMAND.c_str());
    system(SYNC_COMMAND.c_str());
    return 0;
}
