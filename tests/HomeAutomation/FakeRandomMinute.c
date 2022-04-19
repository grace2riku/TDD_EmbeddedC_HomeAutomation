#include "FakeRandomMinute.h"

static int seed = -1;
static int increment = -1;

void FakeRandomMinute_SetFirstAndIncrement(int s, int i)
{
    seed = s;
    increment = i;
}

int FakeRandomMinute_Get(void)
{
    int result = seed;
    seed += increment;
    return result;
}