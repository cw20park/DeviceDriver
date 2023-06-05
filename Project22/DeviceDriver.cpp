#include "DeviceDriver.h"
#include <windows.h>
#include <cstdio>
#include <exception>

#define READ_DELAY (200)
#define ERASED_DATA (0xFF)

DeviceDriver::DeviceDriver(FlashMemoryDevice* hardware) : m_hardware(hardware)
{}

int DeviceDriver::read(long address)
{
    // TODO: implement this method properly
    int firstReadValue = (int)(m_hardware->read(address));
    for (int tryCount = 2; tryCount <= totalReadTryCount; tryCount++)
    {
        Sleep(READ_DELAY);
        int nextReadValue = (int)(m_hardware->read(address));
        if (firstReadValue == nextReadValue) continue;

        throw std::exception("Exception!!");
    }

    return firstReadValue;
}

void DeviceDriver::write(long address, int data)
{
    // TODO: implement this method
    int writtenData = (int)(m_hardware->read(address));

	// 이미 값이 적혀있다면
    if(writtenData != ERASED_DATA)
    {
        throw std::exception("Write Fail Exception");
    }

	m_hardware->write(address, (unsigned char)data);
}