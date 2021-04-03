#include <stdint.h>

#include "TimeService.h"

static Time gs_time;

enum 
{
    INVALID_DAY = -1,
    INVALID_MINUTE = -1
};

void TimeService_Create(void)
{
    gs_time.dayOfWeek = INVALID_DAY;
    gs_time.minuteOfDay = INVALID_MINUTE;
}

void TimeService_Destroy(void)
{
}

void TimeService_GetTime(Time *time)
{
    time->dayOfWeek = gs_time.dayOfWeek;
    time->minuteOfDay = gs_time.minuteOfDay;
}

void FakeTimeService_SetMinute(uint32_t ul_min)
{
    gs_time.minuteOfDay = ul_min;
}

void FakeTimeService_SetDay(uint8_t uc_day)
{
    gs_time.dayOfWeek = uc_day;
}