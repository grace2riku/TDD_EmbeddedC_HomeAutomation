extern "C"
{
#include "Flash.h"
#include "MockIO.h"
#include "m28w160ect.h"
}

#include "CppUTest/TestHarness.h"

TEST_GROUP(Flash)
{
    ioAddress address;
    ioData data;
    int result;

    void setup()
    {
      address = 0x1000;
      data = 0xBEEF;
      result = -1;

      MockIO_Create(10);
      Flash_Create();
    }

    void teardown()
    {
       Flash_Destroy();
       MockIO_Verify_Complete();
       MockIO_Destroy();
    }
};

TEST(Flash, WriteSucceeds_ReadyImmediately)
{
  MockIO_Expect_Write(CommandRegister, ProgramCommand);
  MockIO_Expect_Write(address, data);
  MockIO_Expect_ReadThenReturn(StatusRegister, ReadyBit);
  MockIO_Expect_ReadThenReturn(0x1000, 0xBEEF);
  result = Flash_Write(address, data);
  LONGS_EQUAL(FLASH_SUCCESS, result);
}

