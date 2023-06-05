#include "DeviceDriver.h"
#include <windows.h>
#include <cstdio>
#include <exception>

DeviceDriver::DeviceDriver(FlashMemoryDevice* hardware) : m_hardware(hardware)
{}

int DeviceDriver::read(long address)
{
    // TODO: implement this method properly
    int firstReadValue = (int)(m_hardware->read(address));
    for (int tryCount = 2; tryCount <= totalReadTryCount; tryCount++)
    {
        Sleep(200);
        int nextReadValue = (int)(m_hardware->read(address));
        if (firstReadValue == nextReadValue) continue;

        throw std::exception("Exception!!");
    }

    return firstReadValue;
}

void DeviceDriver::write(long address, int data)
{
    // TODO: implement this method
    m_hardware->write(address, (unsigned char)data);
}