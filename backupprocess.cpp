#include "backupprocess.h"

BackupProcess::BackupProcess() : HomeSecurity()
{

}


int BackupProcess::process()
{
    if(motionHandler->folderSize("/HDD/media/home-security") <= 0)
        return 0;

    system(UNTAR_COMMAND.c_str());
}
