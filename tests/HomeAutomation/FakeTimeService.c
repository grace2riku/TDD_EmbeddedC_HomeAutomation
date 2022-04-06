#include "FakeTimeService.h"

#define NULL 0

static Time fakeTime; 
static WakeUpCallback callback;
static int period;


void FakeTimeService_Create(void)
{
    fakeTime.minuteOfDay = TIME_UNKNOWN;
    fakeTime.dayOfWeek = TIME_UNKNOWN;
}

void FakeTimeService_Destroy(void)
{
}

void TimeService_GetTime(Time* time){
    time->minuteOfDay = fakeTime.minuteOfDay;
    time->dayOfWeek = fakeTime.dayOfWeek;
}

void FakeTimeService_SetMinute(int minute){
    fakeTime.minuteOfDay = minute;
}

void FakeTimeService_SetDay(int day){
    fakeTime.dayOfWeek = day;
}

WakeUpCallback FakeTimeService_GetAlarmCallback(void)
{
    return callback;    
}

int FakeTimeService_GetAlarmPeriod(void)
{
    return period;
}

void TimeService_SetPeriodicAlarmInSeconds(int seconds, WakeUpCallback cb)
{
    callback = cb;
    period = seconds;
}

void TimeService_CancelPeriodicAlarmInSeconds(int seconds, WakeUpCallback cb)
{
    if (cb == callback && period == seconds)
    {
        callback = NULL;
        period = 0;
    }
}

