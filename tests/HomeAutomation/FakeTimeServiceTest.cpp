extern "C"
{
#include "FakeTimeService.h"
}

#include "CppUTest/TestHarness.h"

TEST_GROUP(FakeTimeService)
{
    void setup()
    {
      FakeTimeService_Create();
    }

    void teardown()
    {
       FakeTimeService_Destroy();
    }
};

TEST(FakeTimeService, Create)
{
  Time time;
  TimeService_GetTime(&time);
  LONGS_EQUAL(TIME_UNKNOWN, time.minuteOfDay);
  LONGS_EQUAL(TIME_UNKNOWN, time.dayOfWeek);
}

