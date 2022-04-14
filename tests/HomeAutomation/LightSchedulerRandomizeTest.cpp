extern "C"
{
//#include "LightSchedulerRandomize.h"
#include "LightScheduler.h"
#include "LightControllerSpy.h"
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

