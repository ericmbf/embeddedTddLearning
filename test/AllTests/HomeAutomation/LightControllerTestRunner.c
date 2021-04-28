#if UNIT_TEST
#include "unity.h"
#include "unity_fixture.h"

TEST_GROUP_RUNNER(LightController)
{
    RUN_TEST_CASE(LightController, TurnOn);
}
#endif