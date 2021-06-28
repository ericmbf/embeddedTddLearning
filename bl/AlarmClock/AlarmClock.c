#include "AlarmClock.h"

#include <stdlib.h>
#include <string.h>

#include "Utils.h"
#include "TimeService.h"

#if !UNIT_TEST
#define ALARM_CLOCK_LEN                             10

typedef struct AlarmClockStruct
{
    uint8_t uc_id;
    fp_alarm_clock_cb_t cb;
} s_alarm_clock_t;
#endif

s_alarm_clock_t gas_alarmList[ALARM_CLOCK_LEN];
uint8_t guc_alarmCnt = 0;

void AlarmClock_create()
{
    // Clear alarm count
    guc_alarmCnt = 0;

    for (uint8_t uc_idx = 0; uc_idx < ALARM_CLOCK_LEN; uc_idx++)
    {
        gas_alarmList[uc_idx].uc_id = ALARM_UNKNOWN_ID;
        gas_alarmList[uc_idx].cb = NULL;
        gas_alarmList[uc_idx].ull_tick = ALARM_INVALID_TICK;
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
            gas_alarmList[uc_alarmId].ull_tick = ull_ms;
            gas_alarmList[uc_alarmId].e_state = E_ALARM_STATE_ENABLED;
            
            return true;
        }
    }
        
    return false;
}


void AlarmClock_wakeUp()
{
    Time time;

    TimeService_GetTime(&time);

    for(uint8_t uc_idx = 0; uc_idx < guc_alarmCnt; uc_idx++)
    {
        if((gas_alarmList[uc_idx].e_state == E_ALARM_STATE_ENABLED) &&
            (time.ull_tick >= gas_alarmList[uc_idx].ull_tick))
        {
            gas_alarmList[uc_idx].cb();
        }
    }
}

void AlarmClock_destroyAlarm(uint8_t uc_id)
{
    gas_alarmList[uc_id].uc_id = ALARM_UNKNOWN_ID;
    guc_alarmCnt--;
}

void AlarmClock_disableAlarm(uint8_t uc_id)
{
    gas_alarmList[uc_id].e_state = E_ALARM_STATE_DISABLED;
}

#if UNIT_TEST
uint8_t * AlarmClockSpy_getList()
{
    return (uint8_t*) &gas_alarmList;
}
#endif
