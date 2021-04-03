#include <stdint.h>

typedef enum Day
{
    SUNDAY = 0,
    MONDAY,
    TUESDAY,
    WEDNESDAY,
    THURSDAY,
    FRIDAY,
    SATURDAY,
} Day;


void LightScheduler_Create();
void LightScheduler_Destroy();
void LightScheduler_ScheduleTurnOn(int id, Day day, int minuteOfDay);

#if 0
void LightScheduler_ScreduleTurnOn(uint8_t uc_id, E_DAYWEEK_t e_day, 
    uint32_t ul_time);
#endif
void LightScheduler_WakeUp();