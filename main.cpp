#include <iostream>
#include <string>

using namespace std;

static const string OUTPUT_FILE = "output";
static const string NMAP_COMMAND = "sudo nmap -sP -oG";
static const string IP_GATEWAY = "192.168.0.0/24";

static const string devices[2] = {"192.168.0.20", "192.168.0.21"};

int main()
{

    char* cmd = new char[NMAP_COMMAND.length() + OUTPUT_FILE.length() + IP_GATEWAY.length() + 2];
    sprintf(cmd, "%s %s %s", NMAP_COMMAND.c_str(), OUTPUT_FILE.c_str(), IP_GATEWAY.c_str() );
    system(cmd);
    cout << "Hello World!" << endl;
    return 0;
}
