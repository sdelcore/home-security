#include "cameraprocess.h"
#include "storageprocess.h"

int main(int argc, char *argv[])
{
    CameraProcess cameraProcess(argc, argv);
    StorageProcess storageProcess;

    if(argc == 1)
        return cameraProcess.startDaemon(30);
    else if(argc > 2 || strcmp(argv[1], "-h") == 0)
        cout << "Without an argument, home-security runs as a daemon process"
                "This program only accepts one of the following as arguments:\n"
                "-n : run in non daemon mode\n"
                "-u : untar motion images\n"
                "-x : start daemon for extracting and uploading tar files to Google Drive" << endl;;

    if(strcmp(argv[1], "-n") == 0)
        return cameraProcess.process();
    else if(strcmp(argv[1], "-u") == 0)
        return storageProcess.process();
    else if(strcmp(argv[1], "-r") == 0)
        return storageProcess.startDaemon(60 * 3);
    else
        cout << "Unknown command" << endl;

    return -1;
}
