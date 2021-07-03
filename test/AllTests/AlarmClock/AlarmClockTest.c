#if UNIT_TEST
#include <unity_fixture.h>
#include <unity.h>
#include <string.h>

#include "AlarmClock.h"
#include "TimeService.h"

#if UNIT_TEST && MSP430
#include "msp430.h"
#endif

static void checkCallbackCalled();

TEST_GROUP(AlarmClock);

s_alarm_clock_t * gps_list = NULL;
uint8_t guc_cbCalled = 0;
uint8_t gas_cbCalled[ALARM_CLOCK_LEN];

TEST_SETUP(AlarmClock)
{
    AlarmClock_create();
    FakeTimeService_SetTick(0);
    guc_cbCalled = 0;
    memset(&gas_cbCalled, 0, sizeof(gas_cbCalled));

    gps_list = (s_alarm_clock_t *) AlarmClockSpy_getList();
}

TEST_TEAR_DOWN(AlarmClock)
{
    AlarmClock_destroy();
}

TEST(AlarmClock, clearAllAlarmOnCreate)
{
    // Put trash into alarm list
    for (uint8_t uc_idx = 0; uc_idx < ALARM_CLOCK_LEN; uc_idx++)
    {
        gps_list[uc_idx].uc_id = ALARM_UNKNOWN_ID;
        gps_list[uc_idx].cb = checkCallbackCalled;
        gps_list[uc_idx].ull_tick = 0x123456;
        gps_list[uc_idx].e_state = E_ALARM_STATE_ENABLED;
    }
    
    memset(gps_list, 0xFF, sizeof(gps_list));

    AlarmClock_create();

    for (uint8_t uc_idx = 0; uc_idx < ALARM_CLOCK_LEN; uc_idx++)
    {
        TEST_ASSERT_EQUAL_UINT8(ALARM_UNKNOWN_ID, gps_list[uc_idx].uc_id);
        TEST_ASSERT_EQUAL_PTR(NULL,  gps_list[uc_idx].cb);
        TEST_ASSERT_EQUAL_UINT64(ALARM_INVALID_TICK, gps_list[uc_idx].ull_tick);
        TEST_ASSERT_EQUAL_UINT8(E_ALARM_STATE_AVAILABLE, gps_list[uc_idx].e_state);
    }
}

TEST(AlarmClock, addOneAlarm)
{
    uint8_t uc_idx = 0;

    uc_idx = AlarmClock_createAlarm(checkCallbackCalled);

    TEST_ASSERT_EQUAL_UINT8(0, uc_idx);
}

TEST(AlarmClock, clearAlarmCntOnCreate)
{
    uint8_t uc_expectedFirstValue = 0;
    uint8_t uc_actualValue = 0;

    uc_actualValue = AlarmClock_createAlarm(checkCallbackCalled);
    TEST_ASSERT_EQUAL_UINT8(uc_expectedFirstValue, uc_actualValue);
}

TEST(AlarmClock, addMoreThanOneAlarm)
{
    uint8_t uc_expectedId = 0;

    for (uint8_t uc_idx = 0; uc_idx < ALARM_CLOCK_LEN; uc_idx++)
    {
        uc_idx = AlarmClock_createAlarm(checkCallbackCalled);
        TEST_ASSERT_EQUAL_UINT8(uc_expectedId, uc_idx);
        uc_expectedId++;
    }
}

TEST(AlarmClock, fullAlarmList)
{
    uint8_t uc_idx = 0;

    for (; uc_idx < ALARM_CLOCK_LEN; uc_idx++)
    {
        uc_idx = AlarmClock_createAlarm(checkCallbackCalled);
    }

    uc_idx = AlarmClock_createAlarm(checkCallbackCalled);
    TEST_ASSERT_EQUAL_UINT8(ALARM_UNKNOWN_ID, uc_idx);
}

TEST(AlarmClock, setAlarmIDNotExist)
{
    AlarmClock_createAlarm(checkCallbackCalled);
    
    TEST_ASSERT_FALSE(AlarmClock_setAlarm(1, 0));
}

TEST(AlarmClock, setAlarmIDValidId)
{
    uint8_t uc_validId = AlarmClock_createAlarm(checkCallbackCalled);
    
    AlarmClock_createAlarm(checkCallbackCalled);
    
    TEST_ASSERT_TRUE(AlarmClock_setAlarm(uc_validId, 0));
}

TEST(AlarmClock, isNotTimeYet)
{
    uint8_t uc_idx = 0;

    FakeTimeService_SetTick(1000);

    uc_idx = AlarmClock_createAlarm(checkCallbackCalled);
    
    AlarmClock_setAlarm(uc_idx, 1001);

    AlarmClock_wakeUp();

    TEST_ASSERT_FALSE(gas_cbCalled[uc_idx]);
}

TEST(AlarmClock, createNullPointerCallback)
{
    uint8_t uc_idx = 0;

    uc_idx = AlarmClock_createAlarm(NULL);
    
    TEST_ASSERT_EQUAL_UINT8(ALARM_CALLBACK_NULL_POINTER, uc_idx);
}

TEST(AlarmClock, wakeUpBeforeSetAlarm)
{
    uint8_t uc_idx = 0;

    uc_idx = AlarmClock_createAlarm(checkCallbackCalled);

    AlarmClock_wakeUp();

    TEST_ASSERT_FALSE(gas_cbCalled[uc_idx]);
}

TEST(AlarmClock, isTime)
{
    uint8_t uc_idx = 0;

    uc_idx = AlarmClock_createAlarm(checkCallbackCalled);
    
    AlarmClock_setAlarm(uc_idx, 1100);

    FakeTimeService_SetTick(1100);

    AlarmClock_wakeUp();

    TEST_ASSERT_TRUE(gas_cbCalled[uc_idx]);
}

TEST(AlarmClock, timePast)
{
    uint8_t uc_idx = 0;

    uc_idx = AlarmClock_createAlarm(checkCallbackCalled);
    
    AlarmClock_setAlarm(uc_idx, 1000);

    FakeTimeService_SetTick(2000);

    AlarmClock_wakeUp();

    TEST_ASSERT_TRUE(gas_cbCalled[uc_idx]);
}

TEST(AlarmClock, destroyAlarm)
{
    uint8_t uc_idx = 0;

    uc_idx = AlarmClock_createAlarm(checkCallbackCalled);
    
    AlarmClock_setAlarm(uc_idx, 1000);

    AlarmClock_destroyAlarm(uc_idx);

    FakeTimeService_SetTick(2000);

    AlarmClock_wakeUp();

    TEST_ASSERT_FALSE(gas_cbCalled[uc_idx]);
}

TEST(AlarmClock, useFirstAvailableIdxAlarmAfterDestroyAlarm)
{
    uint8_t uc_idx = 0;

    uc_idx = AlarmClock_createAlarm(checkCallbackCalled);
    uc_idx = AlarmClock_createAlarm(checkCallbackCalled);
    
    AlarmClock_destroyAlarm(0);

    uc_idx = AlarmClock_createAlarm(checkCallbackCalled);

    TEST_ASSERT_EQUAL_UINT8(0, uc_idx);
}

TEST(AlarmClock, disableAlarm)
{
    uint8_t uc_idx = 0;

    uc_idx = AlarmClock_createAlarm(checkCallbackCalled);
    
    AlarmClock_setAlarm(uc_idx, 1000);

    AlarmClock_disableAlarm(uc_idx);

    FakeTimeService_SetTick(1000);

    AlarmClock_wakeUp();

    TEST_ASSERT_FALSE(gas_cbCalled[uc_idx]);
}

TEST(AlarmClock, destroyInvalidId)
{
    uint8_t uc_invalidId = 0;

    AlarmClock_destroyAlarm(uc_invalidId);

    TEST_ASSERT_EQUAL_UINT8(E_ALARM_STATE_AVAILABLE, 
        gps_list[uc_invalidId].e_state);
}

TEST(AlarmClock, disableInvalidAlarm)
{
    uint8_t uc_idxInvalid = 0;
    
    AlarmClock_disableAlarm(uc_idxInvalid);

    TEST_ASSERT_EQUAL_UINT8(E_ALARM_STATE_AVAILABLE, 
        gps_list[uc_idxInvalid].e_state);
}

TEST(AlarmClock, createSetAlarmToDisabled)
{
    uint8_t uc_alarmId = 0;

    uc_alarmId = AlarmClock_createAlarm(checkCallbackCalled);

    TEST_ASSERT_EQUAL_UINT8(E_ALARM_STATE_DISABLED, 
        gps_list[uc_alarmId].e_state);
}

TEST(AlarmClock, setAlarmAfterDisable)
{
    uint8_t uc_alarmId = 0;

    uc_alarmId = AlarmClock_createAlarm(checkCallbackCalled);
    
    AlarmClock_setAlarm(uc_alarmId, 100);

    AlarmClock_disableAlarm(uc_alarmId);

    FakeTimeService_SetTick(100);

    AlarmClock_wakeUp();

    TEST_ASSERT_FALSE(gas_cbCalled[uc_alarmId]);

    AlarmClock_setAlarm(uc_alarmId, 100);
    FakeTimeService_SetTick(200);

    AlarmClock_wakeUp();
    
    TEST_ASSERT_TRUE(gas_cbCalled[uc_alarmId]);
}

TEST(AlarmClock, setTimeOverFlow)
{
    uint8_t uc_alarmId = 0;
    uint64_t ull_overFlow = 0xFFFFFFFFFFFFFFFF;
    uint64_t ull_expectedValue = ull_overFlow + 100;

    uc_alarmId = AlarmClock_createAlarm(checkCallbackCalled);
    
    FakeTimeService_SetTick(ull_overFlow);

    // Overflow set Alarm
    AlarmClock_setAlarm(uc_alarmId, 100);

    TEST_ASSERT_EQUAL_UINT64(ull_expectedValue, gps_list[uc_alarmId].ull_tick);
}

TEST(AlarmClock, AlarmBeforeOverFlow)
{
    uint8_t uc_alarmId = 0;
    uint64_t ull_overFlow = 0xFFFFFFFFFFFFFFFF;

    uc_alarmId = AlarmClock_createAlarm(checkCallbackCalled);
    
    FakeTimeService_SetTick(ull_overFlow - 200);

    AlarmClock_setAlarm(uc_alarmId, 100);

    AlarmClock_wakeUp();

    TEST_ASSERT_FALSE(gas_cbCalled[uc_alarmId]);

    // Time service overflow
    FakeTimeService_SetTick(100);

    AlarmClock_wakeUp();

    TEST_ASSERT_TRUE(gas_cbCalled[uc_alarmId]);
}

TEST(AlarmClock, AlarmSetOverflowNoOverFlowTimeYet)
{
    uint8_t uc_alarmId = 0;
    uint64_t ull_overFlow = 0xFFFFFFFFFFFFFFFF;

    uc_alarmId = AlarmClock_createAlarm(checkCallbackCalled);
    
    FakeTimeService_SetTick(ull_overFlow);

    // Overflow set Alarm
    AlarmClock_setAlarm(uc_alarmId, 100);

    AlarmClock_wakeUp();

    TEST_ASSERT_FALSE(gas_cbCalled[uc_alarmId]);
}

TEST(AlarmClock, AlarmOverflowTimeOverFlowNotTimeYet)
{
    uint8_t uc_alarmId = 0;
    uint64_t ull_overFlow = 0xFFFFFFFFFFFFFFFF;

    uc_alarmId = AlarmClock_createAlarm(checkCallbackCalled);
    
    FakeTimeService_SetTick(ull_overFlow);

    // Overflow set Alarm
    AlarmClock_setAlarm(uc_alarmId, 100);

    // Not time yet
    FakeTimeService_SetTick(50);
    AlarmClock_wakeUp();

    TEST_ASSERT_FALSE(gas_cbCalled[uc_alarmId]);
}

TEST(AlarmClock, AlarmOverflowTimeOverFlowIsTime)
{
    uint8_t uc_alarmId = 0;
    uint64_t ull_overFlow = 0xFFFFFFFFFFFFFFFF;
    uint64_t ull_time = 100;
    uint64_t ull_expectedTime = ull_overFlow + ull_time;

    uc_alarmId = AlarmClock_createAlarm(checkCallbackCalled);
    
    FakeTimeService_SetTick(ull_overFlow);
    AlarmClock_wakeUp();

    // Overflow set Alarm
    AlarmClock_setAlarm(uc_alarmId, ull_time);

    // Not time yet
    FakeTimeService_SetTick(ull_expectedTime);
    AlarmClock_wakeUp();

    TEST_ASSERT_TRUE(gas_cbCalled[uc_alarmId]);
}

static void checkCallbackCalled()
{
    gas_cbCalled[guc_cbCalled] = true;
    guc_cbCalled++;
}
#endif