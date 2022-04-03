#include "LightControllerSpy.h"

static int lastId;
static int lastState;

void LightControllerSpy_Create(void)
{
//    lastId = LIGHT_ID_UNKNOWN;
//    lastState = LIGHT_STATE_UNKNOWN;
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

void LightController_Create(void)
{
    lastId = LIGHT_ID_UNKNOWN;
    lastState = LIGHT_STATE_UNKNOWN;
}

void LightController_Destroy(void)
{

}

void LightController_On(int id)
{
    lastId = id;
    lastState = LIGHT_ON;
}

void LightController_Off(int id)
{
    lastId = id;
    lastState = LIGHT_OFF;
}