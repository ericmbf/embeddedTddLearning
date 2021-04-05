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
    RUN_TEST_CASE(LightScheduler, ScheduleOffEverydayItsTime);
    RUN_TEST_CASE(LightScheduler, ScheduleTuesdayButTisMonday);
    RUN_TEST_CASE(LightScheduler, ScheduleTuesdayAndItsTuesday);
    RUN_TEST_CASE(LightScheduler, ScheduleWeekendItsFriday);
    RUN_TEST_CASE(LightScheduler, ScheduleWeekendItsSatuday);
    RUN_TEST_CASE(LightScheduler, ScheduleWeekendItsSunday);
    RUN_TEST_CASE(LightScheduler, ScheduleWeekdayItsSunday);
    RUN_TEST_CASE(LightScheduler, ScheduleWeekdayItsSaturday);
    RUN_TEST_CASE(LightScheduler, ScheduleWeekdayItsMonday);
    RUN_TEST_CASE(LightScheduler, ScheduleWeekdayItsFriday);
    RUN_TEST_CASE(LightScheduler, ScheduleTwoEventsAtTheSameTime);
    RUN_TEST_CASE(LightScheduler, RejectsTooManyEvents);
    RUN_TEST_CASE(LightScheduler, RemoveRecyclesSheduleSlot);
    RUN_TEST_CASE(LightScheduler, RemoveMultipleScheduleEvent);
    RUN_TEST_CASE(LightScheduler, AcceptsValidLightIds);
    RUN_TEST_CASE(LightScheduler, RejectsInvalidLightIds);
    RUN_TEST_CASE(LightSchedulerInitAndCleanup, CreateStartsOneMinuteAlarm);
    RUN_TEST_CASE(LightSchedulerInitAndCleanup, DestroyCancelsOneMinuteAlarm);

    // RUN_TEST_CASE(LightScheduler, ScheduleOnEverydayNotTimeYet);
}
#endif