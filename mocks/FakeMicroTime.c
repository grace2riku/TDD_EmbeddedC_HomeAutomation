#include "MicroTime.h"

static uint32_t time = 0;
static uint32_t increment = 1;
static uint32_t totalDelay = 0;

void FakeMicroTime_Init(uint32_t start, uint32_t incr)
{
    time = start;
    increment = incr;
    totalDelay = 0;
}

uint32_t MictoTime_Get(void)
{
    uint32_t t = time;
    time += increment;
    return t;
}

