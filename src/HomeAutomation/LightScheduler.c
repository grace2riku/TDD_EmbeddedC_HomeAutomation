#include "LightScheduler.h"
#include "LightController.h"
typedef struct
{
    int id;
    int minuteOfDay;
    int event;
} ScheduledLightEvent;

enum
{
    UNUSED = -1, 
    TURN_OFF, TURN_ON
};

static ScheduledLightEvent scheduledEvent;

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

    if (scheduledEvent.id == UNUSED)
        return;
    if (time.minuteOfDay != scheduledEvent.minuteOfDay)
        return;

    if (scheduledEvent.event == TURN_ON)
        LightController_On(scheduledEvent.id);
    else if (scheduledEvent.event == TURN_OFF)
        LightController_Off(scheduledEvent.id);
}

void LightScheduler_ScheduleTurnOn(int id, Day day, int minuteOfDay)
{
    scheduledEvent.id = id;
    scheduledEvent.minuteOfDay = minuteOfDay;
    scheduledEvent.event = TURN_ON;
}

void LightScheduler_ScheduleTurnOff(int id, Day day, int minuteOfDay)
{
    scheduledEvent.id = id;
    scheduledEvent.minuteOfDay = minuteOfDay;
    scheduledEvent.event = TURN_OFF;
}