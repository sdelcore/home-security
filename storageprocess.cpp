#include "storageprocess.h"

StorageProcess::StorageProcess() : HomeSecurity()
{

}


int StorageProcess::process()
{
    if(motionHandler->folderSize(STORAGE_DIR) <= 0)
        return 0;

    system(UNTAR_COMMAND.c_str());
}
