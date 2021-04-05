#include <stdint.h>

typedef enum E_DAY_t
{
    NONE = -1,
    EVERYDAY = 10,
    WEEKDAY,
    WEEKEND,
    SUNDAY = 1,
    MONDAY,
    TUESDAY,
    WEDNESDAY,
    THURSDAY,
    FRIDAY,
    SATURDAY
} E_DAY_t;

typedef enum E_LS_T
{
    E_LS_UNKNOWN = -1,
    E_LS_OK,
    E_LS_TOO_MANY_EVENTS,
    E_LS_EVENT_DOESNT_EXIST,
    E_LS_ID_OUT_OF_BOUNDS
} E_LS_T;

void LightScheduler_Create(void);
void LightScheduler_Destroy(void);
E_LS_T LightScheduler_ScheduleTurnOn(int id, E_DAY_t day, int minuteOfDay);
E_LS_T LightScheduler_ScheduleTurnOff(int id, E_DAY_t day, int minuteOfDay);
E_LS_T LightScheduler_ScheduleRemove(int id, E_DAY_t day, int minuteOfDay);

#if 0
void LightScheduler_ScreduleTurnOn(uint8_t uc_id, E_DAYWEEK_t e_day, 
    uint32_t ul_time);
#endif
void LightScheduler_WakeUp(void);