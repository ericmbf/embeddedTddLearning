#if UNIT_TEST
#include "unity.h"
#include "unity_fixture.h"

TEST_GROUP_RUNNER(FakeTimeService)
{
    RUN_TEST_CASE(FakeTimeService, Create);
    RUN_TEST_CASE(FakeTimeService, Set);
}
#endif