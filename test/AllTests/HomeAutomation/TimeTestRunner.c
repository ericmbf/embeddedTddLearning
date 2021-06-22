#if UNIT_TEST
#include "unity.h"
#include "unity_fixture.h"

TEST_GROUP_RUNNER(Time)
{
    RUN_TEST_CASE(Time, ExactMatch);
    RUN_TEST_CASE(Time, WeekendDays);
    RUN_TEST_CASE(Time, NotWeekendDays);
    RUN_TEST_CASE(Time, WeekDays);
    RUN_TEST_CASE(Time, NotWeekDays);
    RUN_TEST_CASE(Time, Everyday);
}
#endif