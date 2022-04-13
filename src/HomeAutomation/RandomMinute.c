#include "RandomMinute.h"
#include <stdlib.h> // srand

static int bound = 0;

void RandomMinute_Create(int b)
{
    bound = b;
    srand(10);
}

void RandomMinute_Destroy(void)
{
}

int RandomMinute_Get(void)
{
    return bound - rand() % (bound * 2 + 1);
}