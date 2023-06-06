#include <cstdio>
#include "DeviceDriver.h"

class Application
{
public:
	Application(DeviceDriver* driver) :driver(driver)
	{

	}

	void ReadAndPrint(int start, int end)
	{
		for (int i = start; i <= end; i++)
		{
			int ret = driver->read(i);
			printf("%d\n", ret);
		}
	}

	void WriteAll(int value)
	{
		for (int i = 0x0; i <= 0x4; i++)
		{
			driver->write(i, value);
		}
	}
private:
	DeviceDriver* driver;
};