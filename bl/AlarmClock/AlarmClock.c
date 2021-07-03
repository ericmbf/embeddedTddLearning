#include "AlarmClock.h"

#include <stdlib.h>
#include <string.h>

#include "Utils.h"
#include "TimeService.h"

#if !UNIT_TEST
#define ALARM_CLOCK_OVERFLOW                        0xFFFFFFFFFFFFFFFF
#define ALARM_CLOCK_LEN                             10

typedef struct AlarmClockStruct
{
    uint8_t uc_id;
    fp_alarm_clock_cb_t cb;
} s_alarm_clock_t;
#endif

static bool checkTimeOverFlow(uint64_t ull_tickNow);
static bool isTimeToCallback(s_alarm_clock_t *ps_alarm, bool b_timeOverFlow,
    uint64_t ull_tickNow);
static s_alarm_clock_t gas_alarmList[ALARM_CLOCK_LEN];
static uint8_t guc_alarmCnt = 0;
static uint64_t gull_lastTick = 0;

void AlarmClock_create()
{
    // Clear alarm count
    guc_alarmCnt = 0;

    for (uint8_t uc_idx = 0; uc_idx < ALARM_CLOCK_LEN; uc_idx++)
    {
        gas_alarmList[uc_idx].uc_id = ALARM_UNKNOWN_ID;
        gas_alarmList[uc_idx].cb = NULL;
        gas_alarmList[uc_idx].ull_tick = ALARM_INVALID_TICK;
        gas_alarmList[uc_idx].e_state = E_ALARM_STATE_AVAILABLE;
    }
}

void AlarmClock_destroy()
{
    
}

uint8_t AlarmClock_createAlarm(fp_alarm_clock_cb_t cb)
{
    uint8_t uc_idx;

    if(guc_alarmCnt == ALARM_CLOCK_LEN)
        return ALARM_UNKNOWN_ID;

    if(cb == NULL)
        return ALARM_CALLBACK_NULL_POINTER;

    for (uc_idx = 0; uc_idx < ALARM_CLOCK_LEN; uc_idx++)
    {
        if(gas_alarmList[uc_idx].uc_id == ALARM_UNKNOWN_ID)
        {
            gas_alarmList[uc_idx].uc_id = uc_idx;
            gas_alarmList[uc_idx].cb = cb;
            gas_alarmList[uc_idx].ull_tick = ALARM_INVALID_TICK;
            gas_alarmList[uc_idx].e_state = E_ALARM_STATE_DISABLED;
            guc_alarmCnt++;
            break;
        }
    }
    
    return uc_idx;
}

bool AlarmClock_setAlarm(uint8_t uc_alarmId, uint64_t ull_ms)
{
    for (uint8_t uc_idx = 0; uc_idx < ALARM_CLOCK_LEN; uc_idx++)
    {
        if(gas_alarmList[uc_alarmId].uc_id == uc_alarmId)
        {
            Time time;

            TimeService_GetTime(&time);

            // Set next tick
            gas_alarmList[uc_alarmId].ull_tick = time.ull_tick + ull_ms;

            // Check overflow time
            if((time.ull_tick + ull_ms) < time.ull_tick)
            {
                gas_alarmList[uc_alarmId].b_timeOverFlow = true;
            }
            else
            {
                gas_alarmList[uc_alarmId].b_timeOverFlow = false;
            }

            gas_alarmList[uc_alarmId].e_state = E_ALARM_STATE_ENABLED;
            
            return true;
        }
    }
        
    return false;
}

void AlarmClock_wakeUp()
{
    Time time;
    bool b_timeOverFlow = false;

    // Get actual time
    TimeService_GetTime(&time);

    b_timeOverFlow = checkTimeOverFlow(time.ull_tick);

    for(uint8_t uc_idx = 0; uc_idx < guc_alarmCnt; uc_idx++)
    {
        // Check if alarm is enabled
        if(gas_alarmList[uc_idx].e_state == E_ALARM_STATE_ENABLED)
        {
            if(isTimeToCallback(&gas_alarmList[uc_idx], b_timeOverFlow, 
                time.ull_tick))
            {
                gas_alarmList[uc_idx].cb();
            }
        }
    }
}

void AlarmClock_destroyAlarm(uint8_t uc_id)
{
    if(gas_alarmList[uc_id].e_state > E_ALARM_STATE_AVAILABLE)
    {
        gas_alarmList[uc_id].uc_id = ALARM_UNKNOWN_ID;
        guc_alarmCnt--;
    }
}

void AlarmClock_disableAlarm(uint8_t uc_id)
{
    if(gas_alarmList[uc_id].e_state > E_ALARM_STATE_AVAILABLE)
    {
        gas_alarmList[uc_id].e_state = E_ALARM_STATE_DISABLED;
    }
}

static bool checkTimeOverFlow(uint64_t ull_tickNow)
{
    bool b_ret = false;

    if(gull_lastTick > ull_tickNow)
    {
        b_ret = true;
    }

    gull_lastTick = ull_tickNow;

    return b_ret;
}

static bool isTimeToCallback(s_alarm_clock_t *ps_alarm, bool b_timeOverFlow,
    uint64_t ull_tickNow)
{
    bool b_timeout = false;

    // Check time is past
    b_timeout = (ull_tickNow >= ps_alarm->ull_tick);

    return (!ps_alarm->b_timeOverFlow & b_timeout)                  | 
               (b_timeOverFlow & b_timeout)                         |
               (!ps_alarm->b_timeOverFlow & b_timeOverFlow);
}

#if UNIT_TEST
uint8_t * AlarmClockSpy_getList(void)
{
    return (uint8_t*) &gas_alarmList;
}

uint8_t AlarmClockSpy_getAlarmCnt(void)
{
    return guc_alarmCnt;
}
#endif
