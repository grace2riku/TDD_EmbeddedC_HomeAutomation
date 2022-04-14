#ifndef D_LightScheduler_H
#define D_LightScheduler_H

#include "TimeService.h"

enum { LS_OK, LS_TOO_MANY_EVENTS, LS_ID_OUT_OF_BOUNDS };

/**********************************************************
 *
 * LightScheduler is responsible for ...
 *
 **********************************************************/

void LightScheduler_Create(void);
void LightScheduler_Destroy(void);
void LightScheduler_Wakeup(void);
int LightScheduler_ScheduleTurnOn(int id, Day day, int minuteOfDay);
int LightScheduler_ScheduleTurnOff(int id, Day day, int minuteOfDay);
void LightScheduler_ScheduleRemove(int id, Day day, int minute);
void LightScheduler_Randomize(int id, Day day, int minuteOfDay);

#endif  /* D_FakeLightScheduler_H */
