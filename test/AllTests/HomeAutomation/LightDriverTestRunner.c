#if UNIT_TEST
#include "unity.h"
#include "unity_fixture.h"

TEST_GROUP_RUNNER(LightDriver)
{
    RUN_TEST_CASE(LightDriver, NullDriverDoesNotCrash);
    RUN_TEST_CASE(LightDriver, NullInterfaceDoesNotCrash);
}
#endif