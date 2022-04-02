#ifndef D_TimeService_H
#define D_TimeService_H

typedef struct {
    int minuteOfDay;
    int dayOfWeek;
} Time;

enum {SATURDAY};

void TimeService_Create(void);
void TimeService_Destroy(void);
void TimeService_GetTime(Time* time);

#endif  /* D_FakeLightScheduler_H */
