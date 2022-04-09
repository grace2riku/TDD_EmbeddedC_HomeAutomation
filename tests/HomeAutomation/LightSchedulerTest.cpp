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

#if 0
    void checkLightState(int id, int level)
    {
      LONGS_EQUAL(id, LightControllerSpy_GetLastId());
      LONGS_EQUAL(level, LightControllerSpy_GetLastState());
    }
#endif

    void checkLightState(int id, int level)
    {
      if (id == LIGHT_ID_UNKNOWN)
      {
        LONGS_EQUAL(id, LightControllerSpy_GetLastId());
        LONGS_EQUAL(level, LightControllerSpy_GetLastState());
      }
      else 
      {
        LONGS_EQUAL(level, LightControllerSpy_GetLightState(id));
      }
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

TEST(LightScheduler, ScheduleWeekEndItsMonday)
{
  LightScheduler_ScheduleTurnOn(3, WEEKEND, 1200);
  setTimeTo(MONDAY, 1200);
  LightScheduler_Wakeup();
  checkLightState(LIGHT_ID_UNKNOWN, LIGHT_STATE_UNKNOWN);  
}

TEST(LightScheduler, ScheduleTuesdayButItsMonday)
{
  LightScheduler_ScheduleTurnOn(3, TUESDAY, 1200);
  setTimeTo(MONDAY, 1200);
  LightScheduler_Wakeup();
  checkLightState(LIGHT_ID_UNKNOWN, LIGHT_STATE_UNKNOWN);  
}

TEST(LightScheduler, ScheduleTuesdayAndItsTuesday)
{
  LightScheduler_ScheduleTurnOn(3, TUESDAY, 1200);
  setTimeTo(TUESDAY, 1200);
  LightScheduler_Wakeup();
  checkLightState(3, LIGHT_ON);  
}

TEST(LightScheduler, ScheduleWeekEndItsFriday)
{
  LightScheduler_ScheduleTurnOn(3, WEEKEND, 1200);
  setTimeTo(FRIDAY, 1200);
  LightScheduler_Wakeup();
  checkLightState(LIGHT_ID_UNKNOWN, LIGHT_STATE_UNKNOWN);  
}

TEST(LightScheduler, ScheduleWeekEndItsSaturday)
{
  LightScheduler_ScheduleTurnOn(3, WEEKEND, 1200);
  setTimeTo(SATURDAY, 1200);
  LightScheduler_Wakeup();
  checkLightState(3, LIGHT_ON);  
}

TEST(LightScheduler, ScheduleWeekEndItsSunday)
{
  LightScheduler_ScheduleTurnOn(3, WEEKEND, 1200);
  setTimeTo(SUNDAY, 1200);
  LightScheduler_Wakeup();
  checkLightState(3, LIGHT_ON);  
}

TEST(LightScheduler, WeekdayScheduleNotOperatedOnSunday)
{
  LightScheduler_ScheduleTurnOn(3, WEEKDAY, 1200);
  setTimeTo(SUNDAY, 1200);
  LightScheduler_Wakeup();
  checkLightState(LIGHT_ID_UNKNOWN, LIGHT_STATE_UNKNOWN);  
}

TEST(LightScheduler, WeekdayScheduleIsOperatedOnMonday)
{
  LightScheduler_ScheduleTurnOn(3, WEEKDAY, 1200);
  setTimeTo(MONDAY, 1200);
  LightScheduler_Wakeup();
  checkLightState(3, LIGHT_ON);  
}


TEST_GROUP(LightSchegulerInitAndCleanup)
{  
};

TEST(LightSchegulerInitAndCleanup, CreateStartsOneMinuteAlarm)
{
  LightScheduler_Create();
  POINTERS_EQUAL((void*)LightScheduler_Wakeup,
                (void*)FakeTimeService_GetAlarmCallback());

  LONGS_EQUAL(60, FakeTimeService_GetAlarmPeriod());
  LightScheduler_Destroy();
}

TEST(LightSchegulerInitAndCleanup, DestroyCancelsOneMinuteAlarm)
{
  LightScheduler_Create();
  LightScheduler_Destroy();
  POINTERS_EQUAL(NULL,
                (void*)FakeTimeService_GetAlarmCallback());
}


TEST(LightScheduler, ScheduleTwoEventsAtTheSameTime)
{
  LightScheduler_ScheduleTurnOn(3, SUNDAY, 1200);
  LightScheduler_ScheduleTurnOn(12, SUNDAY, 1200);

  setTimeTo(SUNDAY, 1200);

  LightScheduler_Wakeup();

  checkLightState(3, LIGHT_ON);  
  checkLightState(12, LIGHT_ON);  
}

TEST(LightScheduler, RejectsTooManyEvents)
{
  int i;
  for (i = 0; i < 128; i++)
    LONGS_EQUAL(LS_OK, LightScheduler_ScheduleTurnOn(6, MONDAY, 600+i));

  LONGS_EQUAL(LS_TOO_MANY_EVENTS, LightScheduler_ScheduleTurnOn(6, MONDAY, 600+i));
}

TEST(LightScheduler, RemoveRecyclesScheduleSlot)
{
  int i;
  for (i = 0; i < 128; i++)
    LONGS_EQUAL(LS_OK, LightScheduler_ScheduleTurnOn(6, MONDAY, 600+i));

  LightScheduler_ScheduleRemove(6, MONDAY, 600);

  LONGS_EQUAL(LS_OK, LightScheduler_ScheduleTurnOn(13, MONDAY, 1000));    
}

TEST(LightScheduler, RemoveMultipleScheduledEvent)
{
  LightScheduler_ScheduleTurnOn(6, MONDAY, 600);
  LightScheduler_ScheduleTurnOn(7, MONDAY, 600);
  LightScheduler_ScheduleRemove(6, MONDAY, 600);

  setTimeTo(MONDAY, 600);

  LightScheduler_Wakeup();

  checkLightState(6, LIGHT_STATE_UNKNOWN);
  checkLightState(7, LIGHT_ON);
}