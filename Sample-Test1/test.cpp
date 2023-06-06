#include "gtest/gtest.h"
#include "gmock/gmock.h"
#include "../Project22/DeviceDriver.cpp"
#include "../Project22/App.cpp"

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

TEST(TestCaseName, NormalWrite) {
	MockDevice mock_device;
	EXPECT_CALL(mock_device, read(0xA))
		.WillOnce(Return(ERASED_DATA));
	DeviceDriver driver(&mock_device);
	
	driver.write(0xA, 0x77);
}

TEST(TestCaseName, WriteException) {
	MockDevice mock_device;
	EXPECT_CALL(mock_device, read(0xA))
		.WillOnce(Return(0x23));
	DeviceDriver driver(&mock_device);

	EXPECT_THROW(driver.write(0xA, 0x77), std::exception);
}

TEST(TestCaseName, ApplicationRead)
{
	MockDevice mock_device;
	EXPECT_CALL(mock_device, read)
		.Times(25);

	DeviceDriver driver(&mock_device);
	Application app(&driver);
	app.ReadAndPrint(0x00, 0x04);
}
TEST(TestCaseName, ApplicationWrite)
{
	MockDevice mock_device;
	EXPECT_CALL(mock_device, read)
		.Times(5)
		.WillOnce(Return(ERASED_DATA))
		.WillOnce(Return(ERASED_DATA))
		.WillOnce(Return(ERASED_DATA))
		.WillOnce(Return(ERASED_DATA))
		.WillOnce(Return(ERASED_DATA));
	EXPECT_CALL(mock_device, write)
		.Times(5);

	DeviceDriver driver(&mock_device);
	Application app(&driver);
	app.WriteAll(0x7);
}