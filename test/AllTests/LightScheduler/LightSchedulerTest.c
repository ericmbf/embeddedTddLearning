#if UNIT_TEST
#include <unity_fixture.h>
#include <unity.h>

#include "LightScheduler.h"
#include "LightSchedulerTest.h"
#include "LightControllerSpy.h"
#include "TimeService.h"

#if UNIT_TEST && MSP430
#include "msp430.h"
#endif

enum
{
    EVERYDAY = 1,
};

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
    TEST_ASSERT_EQUAL_INT(LIGHT_ID_UNKNOWN, LightControllerSpy_GetLastId());
    TEST_ASSERT_EQUAL_INT(LIGHT_STATE_UNKNOWN, LightControllerSpy_GetLastState());
}

TEST(LightScheduler, NoScheduleNothingHappens)
{
    FakeTimeService_SetDay(MONDAY);
    FakeTimeService_SetMinute(100);
    LightScheduler_WakeUp();
    TEST_ASSERT_EQUAL_INT(LIGHT_ID_UNKNOWN, LightControllerSpy_GetLastId());
    TEST_ASSERT_EQUAL_INT(LIGHT_STATE_UNKNOWN, LightControllerSpy_GetLastState());
}

TEST(LightScheduler, ScheduleOnEverydayNotTimeYet)
{
    LightScheduler_ScheduleTurnOn(3, EVERYDAY, 1200);
    FakeTimeService_SetDay(MONDAY);
    FakeTimeService_SetMinute(1199);
    LightScheduler_WakeUp();
    TEST_ASSERT_EQUAL_INT(LIGHT_ID_UNKNOWN, LightControllerSpy_GetLastId());
    TEST_ASSERT_EQUAL_INT(LIGHT_STATE_UNKNOWN, LightControllerSpy_GetLastState());
}

TEST(LightScheduler, ScheduleOnEverydayItsTime)
{
    LightScheduler_ScheduleTurnOn(3, EVERYDAY, 1200);
    FakeTimeService_SetDay(MONDAY);
    FakeTimeService_SetMinute(1200);

    LightScheduler_WakeUp();

    TEST_ASSERT_EQUAL_INT(3, LightControllerSpy_GetLastId());
    TEST_ASSERT_EQUAL_INT(LIGHT_ON, LightControllerSpy_GetLastState());
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

#endif