#ifndef D_LightScheduler_H
#define D_LightScheduler_H

#include "TimeService.h"

/**********************************************************
 *
 * LightScheduler is responsible for ...
 *
 **********************************************************/

void LightScheduler_Create(void);
void LightScheduler_Destroy(void);
void LightScheduler_Wakeup(void);
void LightScheduler_ScheduleTurnOn(int id, Day day, int minuteOfDay);

#endif  /* D_FakeLightScheduler_H */
