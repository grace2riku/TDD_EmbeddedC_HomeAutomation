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
//    UNUSED = -1, 
    TURN_OFF, TURN_ON
};

enum
{
    MAX_EVENTS = 128, UNUSED = -1
};

static ScheduledLightEvent scheduledEvent;
static ScheduledLightEvent scheduledEvents[MAX_EVENTS];

static void scheduleEvent(int id, Day day, int minuteOfDay, int event)
{
    int i;

    for (i = 0; i < MAX_EVENTS; i++)
    {
        if (scheduledEvents[i].id == UNUSED)
        {
            scheduledEvents[i].day = day;
            scheduledEvents[i].minuteOfDay = minuteOfDay;
            scheduledEvents[i].event = event;
            scheduledEvents[i].id = id;
            break;
        }
    }
    scheduledEvent.minuteOfDay = minuteOfDay;
    scheduledEvent.event = event;
    scheduledEvent.day = day;
    scheduledEvent.id = id;
}

static void operateLight(ScheduledLightEvent* lightEvent)
{
    if (lightEvent->event == TURN_ON) 
        LightController_On(lightEvent->id);
    else if (lightEvent->event == TURN_OFF)
        LightController_Off(lightEvent->id);
}

#define TRUE (1)
#define FALSE (0)

static int DoesLightRespondToday(Time* time, int reactionDay)
{
    int today = time->dayOfWeek;

    if (reactionDay == EVERYDAY)
        return TRUE;   
    if (reactionDay == today)
        return TRUE;
    if (reactionDay == WEEKEND && (SATURDAY == today || SUNDAY == today) )
        return TRUE;
    if (reactionDay == WEEKDAY && today >= MONDAY && today <= FRIDAY)
        return TRUE;

    return FALSE; 
}

static void processEventDueNow(Time* time, ScheduledLightEvent* lightEvent)
{
    if (lightEvent->id == UNUSED)
        return;
    if (!DoesLightRespondToday(time, lightEvent->day))
        return;
    if (lightEvent->minuteOfDay != time->minuteOfDay)
        return;

    operateLight(lightEvent);
}

void LightScheduler_Create(void)
{
    int i;
    scheduledEvent.id = UNUSED;

    for (i = 0; i < MAX_EVENTS; i++)
        scheduledEvents[i].id = UNUSED;
    TimeService_SetPeriodicAlarmInSeconds(60, LightScheduler_Wakeup);
}

void LightScheduler_Destroy(void)
{
    TimeService_CancelPeriodicAlarmInSeconds(60, LightScheduler_Wakeup);
}

void LightScheduler_Wakeup(void)
{
    int i;
    Time time;
    TimeService_GetTime(&time);

    for (i = 0; i < MAX_EVENTS; i++)
    {
        processEventDueNow(&time, &scheduledEvents[i]);
    }

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