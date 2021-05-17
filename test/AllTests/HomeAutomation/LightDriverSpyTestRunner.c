#if UNIT_TEST
#include "unity.h"
#include "unity_fixture.h"

TEST_GROUP_RUNNER(LightDriverSpy)
{
    RUN_TEST_CASE(LightDriverSpy, Create);
    RUN_TEST_CASE(LightDriverSpy, On);
    RUN_TEST_CASE(LightDriverSpy, LightStateUnknownAfterCreate);
    RUN_TEST_CASE(LightDriverSpy, Off);
    RUN_TEST_CASE(LightDriverSpy, RecordsLastIdLastTurnOn);
    RUN_TEST_CASE(LightDriverSpy, RecordsLastIdLastTurnOff);
}
#endif