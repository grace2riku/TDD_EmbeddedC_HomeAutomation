extern "C"
{
#include "Flash.h"
#include "MockIO.h"
}

#include "CppUTest/TestHarness.h"

TEST_GROUP(Flash)
{
    void setup()
    {
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

TEST(Flash, WriteSucceeds_ReadImmediately)
{
  int result;
  MockIO_Expect_Write(0, 0x40);
  MockIO_Expect_Write(0x1000, 0xBEEF);
  MockIO_Expect_ReadThenReturn(0, 1<<7);
  MockIO_Expect_ReadThenReturn(0x1000, 0xBEEF);
  result = Flash_Write(0x1000, 0xBEEF);
  LONGS_EQUAL(0, result);
  MockIO_Verify_Complete();
}

