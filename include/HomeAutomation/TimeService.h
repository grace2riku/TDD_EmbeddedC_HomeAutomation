#ifndef D_TimeService_H
#define D_TimeService_H

typedef struct {
    int minuteOfDay;
    int dayOfWeek;
} Time;

typedef enum {
    EVERYDAY = -3, WEEKDAY = -2, WEEKEND = -1,
    SUNDAY = 1, MONDAY, TUESDAY, WEDNESDAY, THURSDAY, FRIDAY, SATURDAY
} Day;

void TimeService_Create(void);
void TimeService_Destroy(void);
void TimeService_GetTime(Time* time);

#endif  /* D_FakeLightScheduler_H */
