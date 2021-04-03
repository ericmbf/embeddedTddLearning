#include <stdint.h>

typedef struct TIME
{
    int8_t minuteOfDay;
    int8_t dayOfWeek;
} Time;

void TimeService_Create(void);
void TimeService_Destroy(void);
void TimeService_GetTime(Time *time);
void FakeTimeService_SetMinute(uint32_t ul_min);
void FakeTimeService_SetDay(uint8_t uc_day);
