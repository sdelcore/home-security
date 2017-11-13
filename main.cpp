#include <iostream>
#include <string>
#include <fstream>

using namespace std;

static const string OUTPUT_FILE = "output";
static const string NMAP_COMMAND = "sudo nmap -sP -oG";
static const string IP_GATEWAY = "192.168.0.0/24";

static const string devices[2] = {"192.168.0.20", "192.168.0.21"};

int checkForDevice(const string& file)
{
    string line;
    int loc;
    ifstream output (OUTPUT_FILE);

    if (output.is_open())
    {
        while ( getline (output,line) )
        {
          cout << line << '\n';
          if(line.find(devices[0]) != -1 || line.find(devices[1]) != -1)
          {
              //do something where either of the devices are there
          }
        }
        output.close();
    }
    else
    {
        cout << "Unable to open file" << endl;
    }
}

int main()
{
    char* cmd = new char[NMAP_COMMAND.length() + OUTPUT_FILE.length() + IP_GATEWAY.length() + 2];
    sprintf(cmd, "%s %s %s", NMAP_COMMAND.c_str(), OUTPUT_FILE.c_str(), IP_GATEWAY.c_str() );
    system(cmd);

    checkForDevice();

    delete[] cmd;
    return 0;
}
