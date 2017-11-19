#include "homesecurity.h"

int main(int argc, char *argv[])
{
    HomeSecurity home;

    if(argc == 1)
    {
        return home.startDaemon();
    }
    else if(argc > 2)
        cout << "This program only accepts:\n-n : run in non daemon mode\n-u : upload motion images to server" << endl;;

    if(strcmp(argv[1], "-n") == 0)
    {
        home.process();
        return 0;
    }
    else if(strcmp(argv[1], "-u") == 0)
        return home.backupFiles();
    else
        cout << "Unknown command" << endl;

    return -1;
}
