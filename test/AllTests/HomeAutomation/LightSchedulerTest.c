#if UNIT_TEST
#include <unity_fixture.h>
#include <unity.h>

#include "LightScheduler.h"
#include "LightSchedulerTest.h"
#include "LightControllerSpy.h"
#include "TimeService.h"
#include "FakeRandomMinute.h"

#if UNIT_TEST && MSP430
#include "msp430.h"
#endif

static void setTimeTo(int day, int minuteOfDay);
static void checkLightState(int id, int state);
static int (*savedRandomMinute_get)(void);

TEST_GROUP(LightScheduler);

TEST_SETUP(LightScheduler)
{
    LightController_Create();
    LightScheduler_Create();
}

TEST_TEAR_DOWN(LightScheduler)
{
    LightScheduler_Destroy();
    LightController_Destroy();
}

TEST(LightScheduler, NoChangeToLightsDuringInitialization)
{
    checkLightState(LIGHT_ID_UNKNOWN, LIGHT_STATE_UNKNOWN);
}

TEST(LightScheduler, NoScheduleNothingHappens)
{
    setTimeTo(MONDAY, 100);

    LightScheduler_WakeUp();
    checkLightState(LIGHT_ID_UNKNOWN, LIGHT_STATE_UNKNOWN);
}

TEST(LightScheduler, ScheduleOnEverydayNotTimeYet)
{
    LightScheduler_ScheduleTurnOn(3, EVERYDAY, 1200);
    setTimeTo(MONDAY, 1199);

    LightScheduler_WakeUp();
    checkLightState(LIGHT_ID_UNKNOWN, LIGHT_STATE_UNKNOWN);
}

TEST(LightScheduler, ScheduleOnEverydayItsTime)
{
    LightScheduler_ScheduleTurnOn(3, EVERYDAY, 1200);
    setTimeTo(MONDAY, 1200);

    LightScheduler_WakeUp();

    checkLightState(3, LIGHT_ON);
}

TEST(LightScheduler, ScheduleOffEverydayItsTime)
{
    LightScheduler_ScheduleTurnOff(3, EVERYDAY, 1200);
    setTimeTo(MONDAY, 1200);

    LightScheduler_WakeUp();

    checkLightState(3, LIGHT_OFF);
}

TEST(LightScheduler, ScheduleTuesdayButTisMonday)
{
    LightScheduler_ScheduleTurnOn(3, TUESDAY, 1200);
    setTimeTo(MONDAY, 1200);

    LightScheduler_WakeUp();

    checkLightState(LIGHT_ID_UNKNOWN, LIGHT_STATE_UNKNOWN);
}

TEST(LightScheduler, ScheduleTuesdayAndItsTuesday)
{
    LightScheduler_ScheduleTurnOn(3, TUESDAY, 1200);
    setTimeTo(TUESDAY, 1200);

    LightScheduler_WakeUp();

    checkLightState(3, LIGHT_ON);
}

TEST(LightScheduler, ScheduleWeekendItsFriday)
{
    LightScheduler_ScheduleTurnOn(3, WEEKEND, 1200);
    setTimeTo(FRIDAY, 1200);

    LightScheduler_WakeUp();

    checkLightState(LIGHT_ID_UNKNOWN, LIGHT_STATE_UNKNOWN);
}

TEST(LightScheduler, ScheduleWeekendItsSatuday)
{
    LightScheduler_ScheduleTurnOn(3, WEEKEND, 1200);
    setTimeTo(SATURDAY, 1200);

    LightScheduler_WakeUp();

    checkLightState(3, LIGHT_ON);
}

TEST(LightScheduler, ScheduleWeekendItsSunday)
{
    LightScheduler_ScheduleTurnOn(3, WEEKEND, 1200);
    setTimeTo(SUNDAY, 1200);

    LightScheduler_WakeUp();

    checkLightState(3, LIGHT_ON);
}

TEST(LightScheduler, ScheduleWeekendItsMonday)
{
    LightScheduler_ScheduleTurnOn(3, WEEKEND, 1200);
    setTimeTo(MONDAY, 1200);

    LightScheduler_WakeUp();

    checkLightState(LIGHT_ID_UNKNOWN, LIGHT_STATE_UNKNOWN);
}

TEST(LightScheduler, ScheduleWeekdayItsSunday)
{
    LightScheduler_ScheduleTurnOn(3, WEEKDAY, 1200);
    setTimeTo(SUNDAY, 1200);

    LightScheduler_WakeUp();

    checkLightState(LIGHT_ID_UNKNOWN, LIGHT_STATE_UNKNOWN);
}

TEST(LightScheduler, ScheduleWeekdayItsSaturday)
{
    LightScheduler_ScheduleTurnOn(3, WEEKDAY, 1200);
    setTimeTo(SATURDAY, 1200);

    LightScheduler_WakeUp();

    checkLightState(LIGHT_ID_UNKNOWN, LIGHT_STATE_UNKNOWN);
}

TEST(LightScheduler, ScheduleWeekdayItsMonday)
{
    LightScheduler_ScheduleTurnOn(3, WEEKDAY, 1200);
    setTimeTo(MONDAY, 1200);

    LightScheduler_WakeUp();

    checkLightState(3, LIGHT_ON);
}

TEST(LightScheduler, ScheduleWeekdayItsFriday)
{
    LightScheduler_ScheduleTurnOn(3, WEEKDAY, 1200);
    setTimeTo(FRIDAY, 1200);

    LightScheduler_WakeUp();

    checkLightState(3, LIGHT_ON);
}

TEST(LightScheduler, ScheduleTwoEventsAtTheSameTime)
{
    LightScheduler_ScheduleTurnOn(1, FRIDAY, 1200);
    LightScheduler_ScheduleTurnOn(30, FRIDAY, 1200);
    
    setTimeTo(FRIDAY, 1200);

    LightScheduler_WakeUp();

    checkLightState(1, LIGHT_ON);
    checkLightState(30, LIGHT_ON);
}

TEST(LightScheduler, RejectsTooManyEvents)
{
    uint16_t ui_idx;

    for (ui_idx = 0; ui_idx < 128; ui_idx++)
    {
        TEST_ASSERT_EQUAL_INT(E_LS_OK, 
            LightScheduler_ScheduleTurnOn(6, MONDAY, 600 + ui_idx));
    }

    TEST_ASSERT_EQUAL_INT(E_LS_TOO_MANY_EVENTS, 
        LightScheduler_ScheduleTurnOn(6, MONDAY, 600 + ui_idx));
}

TEST(LightScheduler, RemoveRecyclesSheduleSlot)
{
    uint16_t ui_idx;

    for (ui_idx = 0; ui_idx < 128; ui_idx++)
    {
        TEST_ASSERT_EQUAL_INT(E_LS_OK,
            LightScheduler_ScheduleTurnOn(6, MONDAY, 600 + ui_idx));
    }

    LightScheduler_ScheduleRemove(6, MONDAY, 600);

    TEST_ASSERT_EQUAL_INT(E_LS_OK,  
        LightScheduler_ScheduleTurnOn(13, MONDAY, 1000));
}

TEST(LightScheduler, RemoveMultipleScheduleEvent)
{
    LightScheduler_ScheduleTurnOn(6, MONDAY, 600);
    LightScheduler_ScheduleTurnOn(7, MONDAY, 600);
    LightScheduler_ScheduleRemove(6, MONDAY, 600);

    setTimeTo(MONDAY, 600);

    LightScheduler_WakeUp();

    checkLightState(6, LIGHT_ID_UNKNOWN);
    checkLightState(7, LIGHT_ON);
}

TEST(LightScheduler, AcceptsValidLightIds)
{
    TEST_ASSERT_EQUAL_INT(E_LS_OK, 
        LightScheduler_ScheduleTurnOn(0, MONDAY, 6000));
    TEST_ASSERT_EQUAL_INT(E_LS_OK, 
        LightScheduler_ScheduleTurnOn(15, MONDAY, 6000));
    TEST_ASSERT_EQUAL_INT(E_LS_OK, 
        LightScheduler_ScheduleTurnOn(31, MONDAY, 6000));
}

TEST(LightScheduler, RejectsInvalidLightIds)
{
    TEST_ASSERT_EQUAL_INT(E_LS_ID_OUT_OF_BOUNDS, 
        LightScheduler_ScheduleTurnOn(-1, MONDAY, 6000));
    TEST_ASSERT_EQUAL_INT(E_LS_ID_OUT_OF_BOUNDS, 
        LightScheduler_ScheduleTurnOn(32, MONDAY, 6000));
}

TEST_GROUP(LightSchedulerInitAndCleanup);

TEST_SETUP(LightSchedulerInitAndCleanup)
{
    LightController_Create();
    LightScheduler_Create();
}

TEST_TEAR_DOWN(LightSchedulerInitAndCleanup)
{
    LightScheduler_Destroy();
    LightController_Destroy();
}

TEST(LightSchedulerInitAndCleanup, CreateStartsOneMinuteAlarm)
{
    LightScheduler_Create();
    TEST_ASSERT_POINTERS_EQUAL((void*)LightScheduler_WakeUp, 
        (void*)FakeTimeService_GetAlarmCallback());
    TEST_ASSERT_EQUAL_INT(60, FakeTimeService_GetAlarmPeriod());
    LightScheduler_Destroy();
}

TEST(LightSchedulerInitAndCleanup, DestroyCancelsOneMinuteAlarm)
{
    LightScheduler_Create();
    LightScheduler_Destroy();
    TEST_ASSERT_POINTERS_EQUAL(NULL, (void*)FakeTimeService_GetAlarmCallback());
    TEST_ASSERT_EQUAL_INT(0, FakeTimeService_GetAlarmPeriod());
}

TEST_GROUP(LightSchedulerRandomize);

TEST_SETUP(LightSchedulerRandomize)
{
    LightController_Create();
    LightScheduler_Create();
    UT_PTR_SET(RandomMinute_Get, savedRandomMinute_get);
    RandomMinute_Get = FakeRandomMinute_Get;
}

TEST_TEAR_DOWN(LightSchedulerRandomize)
{
    LightScheduler_Destroy();
    LightController_Destroy();
}

TEST(LightSchedulerRandomize, TurnsOnEarly)
{
    FakeRandomMinute_SetFirstAndIncrement(-10, 5);
    LightScheduler_ScheduleTurnOn(4, EVERYDAY, 600);
    LightScheduler_Randomize(4, EVERYDAY, 600);
    setTimeTo(MONDAY, 600-10);
    LightScheduler_WakeUp();
    checkLightState(4, LIGHT_ON);
}

TEST(LightSchedulerRandomize, TurnsOnAfterTime)
{
    FakeRandomMinute_SetFirstAndIncrement(-10, 5);
    LightScheduler_ScheduleTurnOn(4, EVERYDAY, 600);
    LightScheduler_Randomize(4, EVERYDAY, 600);
    setTimeTo(MONDAY, 600);
    LightScheduler_WakeUp();
    checkLightState(4, LIGHT_ON);
}

#if 0
TEST(LightScheduler, ScheduleOnEverydayNotTimeYet)
{
    LightScheduler_ScreduleTurnOn(3, EVERYDAY, 1200);
    FakeTimeService_SetDay(MONDAY);
    FakeTimeService_SetMinute(1199);
    LightScheduler_WakeUp();

    TEST_ASSERT_LONGS_EQUAL(LIGHT_ID_UNKNOWN, LightControllerSpy_getLastId());
    TEST_ASSERT_LONGS_EQUAL(LIGHT_STATE_UNKNOWN, LightControllerSpy_getLastState());
}
#endif

static void setTimeTo(int day, int minuteOfDay)
{
    FakeTimeService_SetDay(day);
    FakeTimeService_SetMinute(minuteOfDay);
}

static void checkLightState(int id, int state)
{
    if(LIGHT_ID_UNKNOWN == id)
    {
        TEST_ASSERT_EQUAL_INT(id, LightControllerSpy_GetLastId());
        TEST_ASSERT_EQUAL_INT(state, LightControllerSpy_GetLastState());
    }
    else
    {
        TEST_ASSERT_EQUAL_INT(state, LightControllerSpy_GetLightState(id));
    }
}

#endif