#include "motionhandler.h"

MotionHandler::MotionHandler()
{

}

bool MotionHandler::isMotionRunning()
{
    pid_t pid;
    pid = findProcess(MOTION.c_str());
    return pid != -1;
}

pid_t MotionHandler::findProcess(const char* name)
{
    DIR* dir;
    struct dirent* ent;
    char* endptr;
    char buf[512];

    long pid;
    char pname[100] = {0,};
    char state;
    FILE* fp;

    //open /proc directory
    if(!(dir = opendir("/proc")))
    {
        perror("Cannot open /proc");
        return -1;
    }

    while((ent = readdir(dir)) != NULL)
    {
        long lpid = strtol(ent->d_name, &endptr, 10);

        //if endptr is not a null char, directory is not entirely numeric so ignore it
        if(lpid < 0)
            continue;

        //try to open cmdline file
        snprintf(buf, sizeof(buf), "/proc/%ld/stat", lpid);
        fp = fopen(buf, "r");

        if(fp)
        {
            //check the first token in the file, which is the program name
            if((fscanf(fp, "%ld (%[^)]) %c", &pid, pname, &state)) != 3)
            {
                cout << "fscanf failed" << endl;
                fclose(fp);
                closedir(dir);
                return -1;
            }

            if(!strcmp(pname, name))
            {
                fclose(fp);
                closedir(dir);
                return (pid_t) lpid;
            }

            fclose(fp);
        }
    }

    closedir(dir);
    return -1;
}

int MotionHandler::folderSize(const char* folder)
{
    DIR* dir;
    struct dirent* ent;
    struct stat buf;
    int exists;
    int size;

    dir = opendir(folder);

    if(dir == NULL)
    {
        perror("prsize");
        exit(1);
    }

    size = 0;

    for(ent = readdir(dir); ent != NULL; ent = readdir(dir))
    {
        exists = stat(ent->d_name, &buf);

        if(exists < 0)
            fprintf(stderr, "Couldn't stat %s\n", ent->d_name);
        else
            size += buf.st_size;
    }

    closedir(dir);
    return size;
}

string MotionHandler::getTarCommand()
{
    return TAR_COMMAND_START + getTimeDateString() + TAR_COMMAND_END;
}

string MotionHandler::getTimeDateString()
{
    time_t rawtime;
    tm* timeinfo;
    char buffer [80];

    time(&rawtime);
    timeinfo = localtime(&rawtime);

    strftime(buffer,80,"%Y-%m-%d-%H-%M-%S",timeinfo);

    return string(buffer, 80);
}
