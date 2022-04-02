#ifndef D_FakeTimeService_H
#define D_FakeTimeService_H

#include "TimeService.h"

enum {TIME_UNKNOWN = -1};

/**********************************************************
 *
 * FakeTimeService is responsible for ...
 *
 **********************************************************/

void FakeTimeService_Create(void);
void FakeTimeService_Destroy(void);

void FakeTimeService_SetMinute(int minute);
void FakeTimeService_SetDay(int day);

#endif  /* D_FakeFakeTimeService_H */
