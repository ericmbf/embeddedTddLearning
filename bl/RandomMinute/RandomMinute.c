#include "RandomMinute.h"
#include <stdlib.h>
#include <memory.h>

static int bound = 0;

static int RandomMinute_GetImpl(void);

void RandomMinute_Create(int b)
{
    bound = b;
    srand(10);
}

#if 1
static int RandomMinute_GetImpl(void)
{
    return bound - rand() % (bound * 2 + 1);
}

int (*RandomMinute_Get)(void) = RandomMinute_GetImpl;
#else
int RandomMinute_Get(void)
{
    return bound - rand() % (bound * 2 + 1);
}
#endif