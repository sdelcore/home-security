#include <iostream>
#include <string>
#include <fstream>

#include "ping.h"

using namespace std;

static const int SCANS = 3;
static const string OUTPUT_FILE = "output";
static const string NMAP_COMMAND = "sudo nmap -sP -oG";
static const string IP_GATEWAY = "192.168.0.0/24";
static const string DEVICES[2] = {"192.168.0.20", "192.168.0.21"};

/*
 * Performs the nmap command and outputs to the specified file
 */
int performScanCommand(const string& file)
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
bool checkForDevice(const string& file, const string& device)
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

bool scanForDevices()
{
    string file;
    int numberOfDevices = sizeof(DEVICES)/sizeof(DEVICES[0]);

    for(int i = 0; i < SCANS; i++)
    {
        file = OUTPUT_FILE + ".1";
        performScanCommand(file);

        for(int j = 0; j < numberOfDevices; j ++)
        {
            if(checkForDevice(file, DEVICES[0]))
            {
                return true;
            }
        }
    }

    return false;
}

/*
 * Arguments
 * -s # : scan with #s interval
 * -m 0/1 : enable or disable motion
 * -u : upload folder to google drive
 */
int main()
{
    cout << "ping returned " << ping("192.168.0.1") << endl;
    cout << "ping returned " << ping("192.168.0.15") << endl;
    bool found = true;//scanForDevices();

    if(found)
    {

    }
    else
    {

    }


    return 0;
}
