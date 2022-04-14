extern "C"
{
//#include "LightSchedulerRandomize.h"
#include "LightScheduler.h"
#include "LightControllerSpy.h"
#include "FakeTimeService.h"
#include "FakeRandomMinute.h"
}

#include "CppUTest/TestHarness.h"

TEST_GROUP(LightSchedulerRandomize)
{
    void setup()
    {
//      LightSchedulerRandomize_Create();
    }

    void teardown()
    {
//       LightSchedulerRandomize_Destroy();
    }

    void setTimeTo(int day, int minute){
      FakeTimeService_SetDay(day);
      FakeTimeService_SetMinute(minute);
    }

    void checkLightState(int id, int level)
    {
      if (id == LIGHT_ID_UNKNOWN)
      {
        LONGS_EQUAL(id, LightControllerSpy_GetLastId());
        LONGS_EQUAL(level, LightControllerSpy_GetLastState());
      }
      else
        LONGS_EQUAL(level, LightControllerSpy_GetLightState(id));
    }


};

TEST(LightSchedulerRandomize, TurnsOnEarly)
{
  FakeRandomMinute_SetFirstAndIncrement(-10, 5);
  LightScheduler_ScheduleTurnOn(4, EVERYDAY, 600);
  LightScheduler_Randomize(4, EVERYDAY, 600);
  setTimeTo(MONDAY, 600-10);
  LightScheduler_Wakeup();
  checkLightState(4, LIGHT_ON);
}

