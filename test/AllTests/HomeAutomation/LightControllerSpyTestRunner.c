#if UNIT_TEST
#include "unity.h"
#include "unity_fixture.h"

TEST_GROUP_RUNNER(LightControllerSpy)
{
    RUN_TEST_CASE(LightControllerSpy, Create);
    RUN_TEST_CASE(LightControllerSpy, RememberTheLastLightIdControlled);
    RUN_TEST_CASE(LightControllerSpy, RememberAllLightStates);
}
#endif