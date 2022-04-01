#ifndef D_LightControllerSpy_H
#define D_LightControllerSpy_H

/**********************************************************
 *
 * LightControllerSpy is responsible for ...
 *
 **********************************************************/
#include "LightController.h"

enum
{
    LIGHT_ID_UNKNOWN = -1, LIGHT_STATE_UNKNOWN = -1,
    LIGHT_OFF = 0, LUGHT_ON = 1
};

void LightControllerSpy_Create(void);
void LightControllerSpy_Destroy(void);

int LightControllerSpy_GetLastId(void);
int LightControllerSpy_GetLastState(void);

#endif  /* D_FakeLightControllerSpy_H */
