#include "LightScheduler.h"
#include "TimeService.h"
#include "LightControllerSpy.h"
#include "RandomMinute.h"
#include <stdbool.h>

enum
{
    TURN_ON,
    TURN_OFF,
    DIM,
    RANDOM_ON,
    RANDOM_OFF
};

enum
{
    MAX_EVENTS = 128, UNUSED = -1
};

enum
{
    MAX_LIGHTS = 32
};

typedef struct ScheduledLightEvent
{
    int8_t c_id;
    int32_t l_minuteOfDay;
    int e_event;
    E_DAY_t e_day;
    int randomize;
    int randomMinutes;
} ScheduledLightEvent;

static E_LS_T scheduleEvent(int id, E_DAY_t day, int minuteOfDay,
                          int e_evt);
static void processEventDueNow(Time *ps_time,
                               ScheduledLightEvent *ps_lightEvent);
static void operateLight(ScheduledLightEvent *ps_lightEvent);
static bool doesLightRespondToday(Time *ps_time, E_DAY_t e_day);

ScheduledLightEvent gs_schedule;
ScheduledLightEvent gs_scheduleEvents[MAX_EVENTS];

void LightScheduler_Create()
{
    uint8_t uc_idx;

    for(uc_idx = 0; uc_idx < MAX_EVENTS; uc_idx++)
    {
        gs_scheduleEvents[uc_idx].c_id = UNUSED;
    }

    TimeService_SetPeriodAlarmInSeconds(60, LightScheduler_WakeUp);
}

void LightScheduler_Destroy()
{
    TimeService_CancelPeriodAlarmInSeconds(60, LightScheduler_WakeUp);
}

E_LS_T LightScheduler_ScheduleTurnOn(int id, E_DAY_t day, int minuteOfDay)
{
    return scheduleEvent(id, day, minuteOfDay, TURN_ON);
}

E_LS_T LightScheduler_ScheduleTurnOff(int id, E_DAY_t day, int minuteOfDay)
{
    return scheduleEvent(id, day, minuteOfDay, TURN_OFF);
}

E_LS_T LightScheduler_ScheduleRemove(int id, E_DAY_t day, int minuteOfDay)
{
    for (uint8_t uc_idx = 0; uc_idx < MAX_EVENTS; uc_idx++)
    {
        if ((id == gs_scheduleEvents[uc_idx].c_id) &&
            (day == gs_scheduleEvents[uc_idx].e_day) &&
            (minuteOfDay == gs_scheduleEvents[uc_idx].l_minuteOfDay))
        {
            gs_scheduleEvents[uc_idx].c_id = UNUSED;
            return E_LS_OK;
        }
    }
    
    return E_LS_EVENT_DOESNT_EXIST;
}


void LightScheduler_WakeUp(void)
{
    uint8_t uc_idx;
    Time time;

    TimeService_GetTime(&time);

    for (uc_idx = 0; uc_idx < MAX_EVENTS; uc_idx++)
    {
        processEventDueNow(&time, &gs_scheduleEvents[uc_idx]);
    }
}

void LightScheduler_Randomize(int id, E_DAY_t day, int minuteOfDay)
{
    int i;
    for (i = 0; i < MAX_EVENTS; i++)
    {
        ScheduledLightEvent *e = &gs_scheduleEvents[i];
        if (e->c_id == id && e->e_day == day && e->l_minuteOfDay == minuteOfDay)
        {
            e->randomize = RANDOM_ON;
            e->randomMinutes = RandomMinute_Get();
        }
    }
}

static E_LS_T scheduleEvent(int id, E_DAY_t day, int minuteOfDay, 
    int e_evt)
{
    uint8_t uc_idx;

    if(id < 0 || id >= MAX_LIGHTS)
    {
        return E_LS_ID_OUT_OF_BOUNDS;
    }

    for (uc_idx = 0; uc_idx < MAX_EVENTS; uc_idx++)
    {
        if (UNUSED == gs_scheduleEvents[uc_idx].c_id)
        {
            gs_scheduleEvents[uc_idx].c_id = id;
            gs_scheduleEvents[uc_idx].l_minuteOfDay = minuteOfDay;
            gs_scheduleEvents[uc_idx].e_event = e_evt;
            gs_scheduleEvents[uc_idx].e_day = day;
            gs_scheduleEvents[uc_idx].randomize = TURN_OFF;
            gs_scheduleEvents[uc_idx].randomMinutes = 0;
            
            return E_LS_OK;
        }
    }

    return E_LS_TOO_MANY_EVENTS;
}

static void processEventDueNow(Time *ps_time,
                               ScheduledLightEvent *ps_lightEvent)
{
    if (ps_lightEvent->c_id == UNUSED)
        return;
    if (!doesLightRespondToday(ps_time, ps_lightEvent->e_day))
        return;
    if (!(ps_time->l_minuteOfDay >= 
        ps_lightEvent->l_minuteOfDay + ps_lightEvent->randomMinutes))
        return;

    operateLight(ps_lightEvent);
}

static void operateLight(ScheduledLightEvent *ps_lightEvent)
{
    if(TURN_ON == ps_lightEvent->e_event)
    {
        LightController_On(ps_lightEvent->c_id);
    }
    else if(TURN_OFF == ps_lightEvent->e_event)
    {
        LightController_Off(ps_lightEvent->c_id);
    }
}

static bool doesLightRespondToday(Time *ps_time, E_DAY_t e_day)
{
    uint8_t uc_today = ps_time->c_dayOfWeek;
    bool b_ret = false;

    switch (e_day)
    {
    case EVERYDAY:
        b_ret = true;
        break;
    case WEEKEND:
        if ((SATURDAY == uc_today) || (SUNDAY == uc_today))
        {
            b_ret = true;
        }
        break;
    case WEEKDAY:
        if ((uc_today >= MONDAY) && (uc_today <= FRIDAY))
        {
            b_ret = true;
        }

    default:
        if (uc_today == e_day)
        {
            b_ret = true;
        }
        break;
    }

    return b_ret;
}