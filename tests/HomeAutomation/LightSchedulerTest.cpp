extern "C"
{
#include "LightScheduler.h"
#include "LightControllerSpy.h"
#include "FakeTimeService.h"
}

#include "CppUTest/TestHarness.h"

TEST_GROUP(LightScheduler)
{
    void setup()
    {
      LightScheduler_Create();
      LightController_Create();
    }

    void teardown()
    {
       LightScheduler_Destroy();
       LightController_Destroy();
    }

    void setTimeTo(int day, int minuteOfDay)
    {
      FakeTimeService_SetDay(day);
      FakeTimeService_SetMinute(minuteOfDay);
    }

    void checkLightState(int id, int level)
    {
      LONGS_EQUAL(id, LightControllerSpy_GetLastId());
      LONGS_EQUAL(level, LightControllerSpy_GetLastState());
    }

};

#if 0
TEST(LightScheduler, Create)
{
  FAIL("Start here");
}
#endif

#if 1
TEST(LightScheduler, ScheduleOnEverydayNotTimeYet)
{
  LightScheduler_ScheduleTurnOn(3, EVERYDAY, 1200);
  setTimeTo(MONDAY, 1199);
  LightScheduler_Wakeup();

  checkLightState(LIGHT_ID_UNKNOWN, LIGHT_STATE_UNKNOWN);  
}
#endif

TEST(LightScheduler, NoChangeToLightDuringInitialization)
{
  checkLightState(LIGHT_ID_UNKNOWN, LIGHT_STATE_UNKNOWN);  
}

TEST(LightScheduler, NoScheduleNothingHappens)
{
  setTimeTo(MONDAY, 1200);
  LightScheduler_Wakeup();
  checkLightState(LIGHT_ID_UNKNOWN, LIGHT_STATE_UNKNOWN);  
}

TEST(LightScheduler, ScheduleOnEverydayItsTime)
{
  LightScheduler_ScheduleTurnOn(3, EVERYDAY, 1200);
  setTimeTo(MONDAY, 1200);

  LightScheduler_Wakeup();

  checkLightState(3, LIGHT_ON);  
}

TEST(LightScheduler, ScheduleOffEverydayItsTime)
{
  LightScheduler_ScheduleTurnOff(3, EVERYDAY, 1200);
  setTimeTo(MONDAY, 1200);

  LightScheduler_Wakeup();

  checkLightState(3, LIGHT_OFF);  
}
