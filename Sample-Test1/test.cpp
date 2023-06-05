#include "gtest/gtest.h"
#include "gmock/gmock.h"
#include "../Project22/DeviceDriver.cpp"

using namespace testing;
using namespace std;

class MockDevice : public FlashMemoryDevice
{
public:
	MOCK_METHOD(unsigned char, read, (long address), (override));
	MOCK_METHOD(void, write, (long address, unsigned char data), (override));
};

TEST(TestCaseName, FiveRead) {
	MockDevice mock_device;
	EXPECT_CALL(mock_device, read)
		.Times(5);

	DeviceDriver driver(&mock_device);
	driver.read(0xA);
}

TEST(TestCaseName, Exception) {
	MockDevice mock_device;
	
	EXPECT_CALL(mock_device, read(0x2))
		.WillOnce(Return(0x7))
		.WillOnce(Return(0x7))
		.WillOnce(Return(0x7))
		.WillOnce(Return(0x7))
		.WillOnce(Return(0x3));

	DeviceDriver driver(&mock_device);
	EXPECT_THROW(driver.read(0x2), std::exception);
}