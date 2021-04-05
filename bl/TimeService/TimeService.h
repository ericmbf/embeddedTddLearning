#include <stdint.h>

typedef struct TIME
{
    int32_t l_minuteOfDay;
    int8_t c_dayOfWeek;
} Time;

typedef void (*f_wakeup_callback_t)(void);

void TimeService_Create(void);
void TimeService_Destroy(void);
void TimeService_GetTime(Time *time);
void TimeService_SetPeriodAlarmInSeconds(int seconds, 
    f_wakeup_callback_t fp_callback);
void TimeService_CancelPeriodAlarmInSeconds(int seconds, 
    f_wakeup_callback_t pf_callback);

void FakeTimeService_SetMinute(uint32_t ul_min);
void FakeTimeService_SetDay(uint8_t uc_day);
f_wakeup_callback_t FakeTimeService_GetAlarmCallback(void);
int FakeTimeService_GetAlarmPeriod();