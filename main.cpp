#include "devicehandler.h"

int main()
{
    DeviceHandler dev;
    bool deviceFound = dev.scanForDevices();

    if(deviceFound)
    {
        //start motion
    }
    else
    {
        //stop motion
    }

    return 0;
}
