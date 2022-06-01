#include <CppUTestExt/MockSupport.h>

extern "C"
{
#include "Flash.h"
#include "MockIO.h"
#include "m28w160ect.h"
#include "FakeMicroTime.h"

void CppUMock_IO_Write(ioAddress address, ioData data)
{
  mock().actualCall("IO_Write")
        .withIntParameter("address", (int)address)
        .withIntParameter("data", (int)data);
}

ioData CppUMock_IO_Read(ioAddress address)
{
  mock().actualCall("IO_Read")
        .withIntParameter("address", (int)address);

  return mock().returnValue().getIntValue();
}
}

#include "CppUTest/TestHarness.h"
#include <CppUTestExt/MockSupport.h>

TEST_GROUP(FlashTest_CppUMock)
{
    ioAddress address;
    ioData data;
    int result;

    void setup()
    {
      UT_PTR_SET(IO_Write, CppUMock_IO_Write);
      UT_PTR_SET(IO_Read, CppUMock_IO_Read);

      address = 0x1000;
      data = 0xBEEF;
      result = -1;

//      MockIO_Create(20);
      FakeMicroTime_Init(0, 1);
      Flash_Create();
    }

    void teardown()
    {
       Flash_Destroy();
       mock().checkExpectations();
       mock().clear();
//       MockIO_Verify_Complete();
//       MockIO_Destroy();
    }

    void expectCommand(ioData command)
    {
      mock().expectOneCall("IO_Write")
            .withParameter("address", CommandRegister)
            .withParameter("data", command);
    }

    void expectWriteData()
    {
      mock().expectOneCall("IO_Write")
            .withParameter("address", address)
            .withParameter("data", data);
    }

    void simulateDeviceStatus(ioData status)
    {
      mock().expectOneCall("IO_Read")
            .withParameter("address", StatusRegister)
            .andReturnValue((int)status);
    }

    void simulateReadback(ioData data)
    {
      mock().expectOneCall("IO_Read")
            .withParameter("address", address)
            .andReturnValue((int)data);
    }

    void simulateDeviceStatusWithRepeat(ioData status, int repeatCount)
    {
      mock().expectNCalls(repeatCount, "IO_Read")
            .withParameter("address", StatusRegister)
            .andReturnValue((int)status);
    }
};


TEST(FlashTest_CppUMock, WriteSucceeds_ReadyImmediately)
{
//  mock().expectOneCall("IO_Write")
//        .withParameter("address", CommandRegister)
//        .withParameter("data", ProgramCommand);

  expectCommand(ProgramCommand);

//  mock().expectOneCall("IO_Write")
//        .withParameter("address", address)
//        .withParameter("data", data);

  expectWriteData();

//  mock().expectOneCall("IO_Read")
//        .withParameter("address", StatusRegister)
//        .andReturnValue((int)ReadyBit);

  simulateDeviceStatus(ReadyBit);  

//  mock().expectOneCall("IO_Read")
//        .withParameter("address", address)
//        .andReturnValue((int)data);

  simulateReadback(data);

  int result = Flash_Write(address, data);

  LONGS_EQUAL(FLASH_SUCCESS, result);

#if 0
  MockIO_Expect_Write(CommandRegister, ProgramCommand);
  MockIO_Expect_Write(address, data);
  MockIO_Expect_ReadThenReturn(StatusRegister, ReadyBit);
  MockIO_Expect_ReadThenReturn(address, data);
  result = Flash_Write(address, data);
  LONGS_EQUAL(FLASH_SUCCESS, result);
#endif
}

TEST(FlashTest_CppUMock, SucceedsNotImmediatelyReady)
{
//  mock().expectOneCall("IO_Write")
//        .withParameter("address", CommandRegister)
//        .withParameter("data", ProgramCommand);

  expectCommand(ProgramCommand);

//  mock().expectOneCall("IO_Write")
//        .withParameter("address", address)
//        .withParameter("data", data);

  expectWriteData();

//  mock().expectOneCall("IO_Read")
//        .withParameter("address", StatusRegister)
//        .andReturnValue(0);
//  mock().expectOneCall("IO_Read")
//        .withParameter("address", StatusRegister)
//        .andReturnValue(0);
//  mock().expectOneCall("IO_Read")
//        .withParameter("address", StatusRegister)
//        .andReturnValue(0);

  simulateDeviceStatusWithRepeat(0, 3);

//  mock().expectOneCall("IO_Read")
//        .withParameter("address", StatusRegister)
//        .andReturnValue(ReadyBit);

  simulateDeviceStatus(ReadyBit);

//  mock().expectOneCall("IO_Read")
//        .withParameter("address", address)
//        .andReturnValue(data);

  simulateReadback(data);

  int result = Flash_Write(address, data);

  LONGS_EQUAL(FLASH_SUCCESS, result);

#if 0
TEST(Flash, SucceedsNotImmediatelyReady)
{
  MockIO_Expect_Write(CommandRegister, ProgramCommand);
  MockIO_Expect_Write(address, data);
  MockIO_Expect_ReadThenReturn(StatusRegister, 0);
  MockIO_Expect_ReadThenReturn(StatusRegister, 0);
  MockIO_Expect_ReadThenReturn(StatusRegister, 0);
  MockIO_Expect_ReadThenReturn(StatusRegister, ReadyBit);
  MockIO_Expect_ReadThenReturn(address, data);

  result = Flash_Write(address, data);
  LONGS_EQUAL(FLASH_SUCCESS, result);
}
#endif
}

TEST(FlashTest_CppUMock, WriteFails_VppError)
{
  expectCommand(ProgramCommand);
  expectWriteData();
  simulateDeviceStatus(ReadyBit | VppErrorBit);
  expectCommand(Reset);

  result = Flash_Write(address, data);

  LONGS_EQUAL(FLASH_VPP_ERROR, result);

#if 0
TEST(Flash, WriteFails_VppError)
{
  MockIO_Expect_Write(CommandRegister, ProgramCommand);
  MockIO_Expect_Write(address, data);
  MockIO_Expect_ReadThenReturn(StatusRegister, ReadyBit | VppErrorBit);
  MockIO_Expect_Write(CommandRegister, Reset);

  result = Flash_Write(address, data);

  LONGS_EQUAL(FLASH_VPP_ERROR, result);
}
#endif
}

#if 0
TEST(Flash, WriteFails_VppError)
{
  MockIO_Expect_Write(CommandRegister, ProgramCommand);
  MockIO_Expect_Write(address, data);
  MockIO_Expect_ReadThenReturn(StatusRegister, ReadyBit | VppErrorBit);
  MockIO_Expect_Write(CommandRegister, Reset);

  result = Flash_Write(address, data);

  LONGS_EQUAL(FLASH_VPP_ERROR, result);
}

TEST(Flash, WriteFails_FlashReadBackError)
{
  MockIO_Expect_Write(CommandRegister, ProgramCommand);
  MockIO_Expect_Write(address, data);
  MockIO_Expect_ReadThenReturn(StatusRegister, ReadyBit);
  MockIO_Expect_ReadThenReturn(address, data-1);

  result = Flash_Write(address, data);

  LONGS_EQUAL(FLASH_READ_BACK_ERROR, result);
}

TEST(Flash, WriteFails_IgnoresOtherBitsUntilReady)
{
  MockIO_Expect_Write(CommandRegister, ProgramCommand);
  MockIO_Expect_Write(address, data);
  MockIO_Expect_ReadThenReturn(StatusRegister, ~ReadyBit);
  MockIO_Expect_ReadThenReturn(StatusRegister, ReadyBit);
  MockIO_Expect_ReadThenReturn(address, data);

  result = Flash_Write(address, data);

  LONGS_EQUAL(FLASH_SUCCESS, result);
}

TEST(Flash, WriteFails_Timeout)
{
  FakeMicroTime_Init(0, 500);
  Flash_Create();

  MockIO_Expect_Write(CommandRegister, ProgramCommand);
  MockIO_Expect_Write(address, data);
  for (int i = 0; i < 10; i++)
    MockIO_Expect_ReadThenReturn(StatusRegister, ~ReadyBit);
  result = Flash_Write(address, data);
  LONGS_EQUAL(FLASH_TIMEOUT_ERROR, result);
}

TEST(Flash, WriteFails_TimeoutAtEndTime)
{
  FakeMicroTime_Init(0xffffffff, 500);
  Flash_Create();

  MockIO_Expect_Write(CommandRegister, ProgramCommand);
  MockIO_Expect_Write(address, data);
  for (int i = 0; i < 10; i++)
    MockIO_Expect_ReadThenReturn(StatusRegister, ~ReadyBit);
  result = Flash_Write(address, data);
  LONGS_EQUAL(FLASH_TIMEOUT_ERROR, result);
}
#endif
