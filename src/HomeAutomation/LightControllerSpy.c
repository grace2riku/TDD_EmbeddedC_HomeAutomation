#include "LightControllerSpy.h"

static int lastId;
static int lastState;

void LightControllerSpy_Create(void)
{
    lastId = LIGHT_ID_UNKNOWN;
    lastState = LIGHT_STATE_UNKNOWN;
}

void LightControllerSpy_Destroy(void)
{
}

int LightControllerSpy_GetLastId(void)
{
    return lastId;
}

int LightControllerSpy_GetLastState(void)
{
    return lastState;
}
