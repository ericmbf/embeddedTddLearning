#if UNIT_TEST
#include "unity.h"
#include "unity_fixture.h"

#include "LightSchedulerTest.h"

TEST_GROUP_RUNNER(LightScheduler)
{
    RUN_TEST_CASE(LightScheduler, NoChangeToLightsDuringInitialization);
    RUN_TEST_CASE(LightScheduler, NoScheduleNothingHappens);
    RUN_TEST_CASE(LightScheduler, ScheduleOnEverydayNotTimeYet);
    RUN_TEST_CASE(LightScheduler, ScheduleOnEverydayItsTime);
    // RUN_TEST_CASE(LightScheduler, ScheduleOnEverydayNotTimeYet);
}
#endif