#include "LightScheduler.h"
#include "LightController.h"
typedef struct
{
    int id;
    Day day;
    int minuteOfDay;
    int event;
} ScheduledLightEvent;

enum
{
    UNUSED = -1, 
    TURN_OFF, TURN_ON
};

static ScheduledLightEvent scheduledEvent;

static void scheduleEvent(int id, Day day, int minuteOfDay, int event)
{
    scheduledEvent.minuteOfDay = minuteOfDay;
    scheduledEvent.event = event;
    scheduledEvent.id = id;
}

static void operateLight(ScheduledLightEvent* lightEvent)
{
    if (lightEvent->event == TURN_ON) 
        LightController_On(lightEvent->id);
    else if (lightEvent->event == TURN_OFF)
        LightController_Off(lightEvent->id);
}

static void processEventDueNow(Time* time, ScheduledLightEvent* lightEvent)
{
    if (lightEvent->id == UNUSED)
        return;
    if (lightEvent->day != EVERYDAY)
        return;
    if (lightEvent->minuteOfDay != time->minuteOfDay)
        return;

    operateLight(lightEvent);
}

void LightScheduler_Create(void)
{
    scheduledEvent.id = UNUSED;
}

void LightScheduler_Destroy(void)
{
}

void LightScheduler_Wakeup(void)
{
    Time time;
    TimeService_GetTime(&time);

    processEventDueNow(&time, &scheduledEvent);
}

void LightScheduler_ScheduleTurnOn(int id, Day day, int minuteOfDay)
{
    scheduleEvent(id, day, minuteOfDay, TURN_ON);
}

void LightScheduler_ScheduleTurnOff(int id, Day day, int minuteOfDay)
{
    scheduleEvent(id, day, minuteOfDay, TURN_OFF);
}