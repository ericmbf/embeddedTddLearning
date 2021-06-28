#if UNIT_TEST
#include "unity.h"
#include "unity_fixture.h"

TEST_GROUP_RUNNER(LightController)
{
    RUN_TEST_CASE(LightController, TurnOn);
    RUN_TEST_CASE(LightController, AddingDriverDestroysPrevious);
    RUN_TEST_CASE(LightController, turnOnDifferentDriverTypes);
}
#endif