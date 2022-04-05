#include "FakeTimeService.h"

static Time fakeTime; 

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
    return 0;    
}

int FakeTimeService_GetAlarmPeriod(void)
{
    return 0;
}