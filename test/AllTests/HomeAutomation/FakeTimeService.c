#include <stdint.h>
#include <stddef.h>

#include "TimeService.h"

static Time gs_time;

enum 
{
    INVALID_DAY = -1,
    INVALID_MINUTE = -1
};

static f_wakeup_callback_t gfp_wakeCallback;
static int gul_periodAlarm = 0;

void TimeService_Create(void)
{
    gs_time.c_dayOfWeek = INVALID_DAY;
    gs_time.l_minuteOfDay = INVALID_MINUTE;
}

void TimeService_Destroy(void)
{
}

void TimeService_GetTime(Time *time)
{
    time->c_dayOfWeek = gs_time.c_dayOfWeek;
    time->l_minuteOfDay = gs_time.l_minuteOfDay;
    time->ull_tick = gs_time.ull_tick;
}

void TimeService_SetPeriodAlarmInSeconds(int seconds, 
    f_wakeup_callback_t pf_callback)
{
    gul_periodAlarm = seconds;
    gfp_wakeCallback = pf_callback;
}

void TimeService_CancelPeriodAlarmInSeconds(int seconds, 
    f_wakeup_callback_t pf_callback)
{
    if((pf_callback == gfp_wakeCallback) && (seconds == gul_periodAlarm))
    {
        gfp_wakeCallback = NULL;
        gul_periodAlarm = 0;
    }
}

void FakeTimeService_SetMinute(uint32_t ul_min)
{
    gs_time.l_minuteOfDay = ul_min;
}

void FakeTimeService_SetDay(uint8_t uc_day)
{
    gs_time.c_dayOfWeek = uc_day;
}

void FakeTimeService_SetTick(uint64_t ull_tick)
{
    gs_time.ull_tick = ull_tick;
}

f_wakeup_callback_t FakeTimeService_GetAlarmCallback(void)
{
    return gfp_wakeCallback;
}

int FakeTimeService_GetAlarmPeriod()
{
    return gul_periodAlarm;
}