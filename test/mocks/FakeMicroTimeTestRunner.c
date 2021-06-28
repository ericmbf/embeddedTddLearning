#if UNIT_TEST
#include "unity.h"
#include "unity_fixture.h"

TEST_GROUP_RUNNER(FakeMicroTime)
{
    RUN_TEST_CASE(FakeMicroTime, Create);
    RUN_TEST_CASE(FakeMicroTime, MicroTimeIncrements);
    RUN_TEST_CASE(FakeMicroTime, MicroTimeDelay);
    RUN_TEST_CASE(FakeMicroTime, MicroTimeDelayRecording);
}
#endif