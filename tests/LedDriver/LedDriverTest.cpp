extern "C"
{
#include "LedDriver.h"
#include "RuntimeErrorStub.h"
}

#include "CppUTest/TestHarness.h"

TEST_GROUP(LedDriver)
{
    uint16_t virtualLeds; // TEST_GROUPの中の変数はTEST_GROUPで共有できる
    void setup()  // setupは各TEST実行の際に呼び出される
    {
      LedDriver_Create(&virtualLeds);
    }

    void teardown()
    {
    }
};

// テストは下に書いてあるものから先に実行される

TEST(LedDriver, LedsOffAfterCreate)
{
  virtualLeds = 0xffff;
  LedDriver_Create(&virtualLeds);
  LONGS_EQUAL(0, virtualLeds);
}

TEST(LedDriver, TurnOnLedOne)
{
  LedDriver_TurnOn(1);
  LONGS_EQUAL(1, virtualLeds);
}

TEST(LedDriver, TurnOffLedOne)
{
  LedDriver_TurnOn(1);
  LedDriver_TurnOff(1);
  LONGS_EQUAL(0, virtualLeds);
}

TEST(LedDriver, TurnOnMultipleLeds)
{
  LedDriver_TurnOn(9);
  LedDriver_TurnOn(8);
  LONGS_EQUAL(0x180, virtualLeds);  
}

TEST(LedDriver, AllOn)
{
  LedDriver_TurnAllOn();
  LONGS_EQUAL(0xffff, virtualLeds);
}

TEST(LedDriver, TurnOffAnyLed)
{
  LedDriver_TurnAllOn();
  LedDriver_TurnOff(8);
  LONGS_EQUAL(0xff7f, virtualLeds);
}

TEST(LedDriver, LedMemoryIsNotReadable)
{
  virtualLeds = 0xffff;
  LedDriver_TurnOn(8);
  LONGS_EQUAL(0x80, virtualLeds);
}

TEST(LedDriver, UpperAndLowerBounds)
{
  LedDriver_TurnOn(1);
  LedDriver_TurnOn(16);
  LONGS_EQUAL(0x8001, virtualLeds);
}

TEST(LedDriver, OutOfBoundsChangesNothing)
{
  LedDriver_TurnOn(-1);
  LedDriver_TurnOn(0);
  LedDriver_TurnOn(17);
  LedDriver_TurnOn(3141);
  LONGS_EQUAL(0, virtualLeds);
}

TEST(LedDriver, OutOfBoundsTurnOffDoesNoHarm)
{
  LedDriver_TurnAllOn();
  LedDriver_TurnOff(-1);
  LedDriver_TurnOff(0);
  LedDriver_TurnOff(17);
  LedDriver_TurnOff(3141);
  LONGS_EQUAL(0xffff, virtualLeds);
}

TEST(LedDriver, OutOfBoundsProducesRuntimeError)
{
  LedDriver_TurnOn(-1);
  STRCMP_EQUAL("LED Driver: out-of-bounds LED", RuntimeErrorStub_GetLastError());
  LONGS_EQUAL(-1, RuntimeErrorStub_GetLastParameter());
}

IGNORE_TEST(LedDriver, OutOfBoundsTodo)
{
  /* TODO: 実行中に何をするべきだろうか? */
}

TEST(LedDriver, IsOn)
{
  CHECK_EQUAL(FALSE, LedDriver_IsOn(11));
  LedDriver_TurnOn(11);
  CHECK_EQUAL(TRUE, LedDriver_IsOn(11));
}

TEST(LedDriver, OutOfBoundsLedsAreAlwaysOff)
{
  CHECK_EQUAL(FALSE, LedDriver_IsOn(0));
  CHECK_EQUAL(FALSE, LedDriver_IsOn(17));
}

TEST(LedDriver, IsOff)
{
  CHECK_EQUAL(TRUE, LedDriver_IsOff(12));
  LedDriver_TurnOn(12);
  CHECK_EQUAL(FALSE, LedDriver_IsOff(12));
}

TEST(LedDriver, TurnOffMultipleLeds)
{
  LedDriver_TurnAllOn();
  LedDriver_TurnOff(9);
  LedDriver_TurnOff(8);
  LONGS_EQUAL((~0x180)&0xffff, virtualLeds);
}

TEST(LedDriver, AllOff)
{
  LedDriver_TurnAllOn();
  LedDriver_TurnAllOff();
  LONGS_EQUAL(0, virtualLeds);
}