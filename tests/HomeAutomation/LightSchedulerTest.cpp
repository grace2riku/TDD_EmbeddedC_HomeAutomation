extern "C"
{
#include "LightScheduler.h"
}

#include "CppUTest/TestHarness.h"

TEST_GROUP(LightScheduler)
{
    void setup()
    {
      LightScheduler_Create();
    }

    void teardown()
    {
       LightScheduler_Destroy();
    }
};

#if 1
TEST(LightScheduler, Create)
{
  FAIL("Start here");
}
#endif

#if 0
TEST(LightScheduler, ScheduleOnEverydayNotTimeYet)
{
  LightScheduler_SchduleTurnOn(3, EVERYDAY, 1200);
  FakeTimeService_SetDay(MONDAY);
  FakeTimeService_SetMinute(1199);
  LightScheduler_Wakeup();

  LONGS_EQUAL(LIGHT_ID_UNKNOW, LightControllerSpy_GetLastId());
  LONGS_EQUAL(LIGHT_STATE_UNKNOW, LightControllerSpy_GetLastState());
}
#endif
