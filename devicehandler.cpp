#include "devicehandler.h"

DeviceHandler::DeviceHandler()
{

}

/*
 * Performs the nmap command and outputs to the specified file
 */
int DeviceHandler::performScanCommand(const string& file)
{
    char* cmd = new char[NMAP_COMMAND.length() + file.length() + IP_GATEWAY.length() + 2];
    sprintf(cmd, "%s %s %s", NMAP_COMMAND.c_str(), file.c_str(), IP_GATEWAY.c_str() );
    int ret = system(cmd);
    delete[] cmd;
    return ret;
}

/*
 * checks the provided file for if the device IP appears
 */
bool DeviceHandler::checkForDeviceInFile(const string& file, const string& device)
{
    string line;
    ifstream output (file);

    if (output.is_open())
    {
        while ( getline (output,line) )
        {
          cout << line << '\n';
          if(line.find(device) != string::npos)
          {
              return true;
          }
        }
        output.close();
    }
    else
    {
        cout << "Unable to open file" << endl;
    }

    return false;
}

bool DeviceHandler::scanForDevices()
{
    int numberOfDevices = sizeof(DEVICES)/sizeof(DEVICES[0]);

    for(int i = 0; i < numberOfDevices; i ++)
    {
        if(ping(DEVICES[i]) > 0)
            return true;
    }

    return false;
}
