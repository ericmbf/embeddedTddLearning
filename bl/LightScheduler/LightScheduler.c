#include "LightScheduler.h"
#include "TimeService.h"
#include "LightControllerSpy.h"
#include <stdbool.h>

enum
{
    UNUSED = -1,
    TURN_OFF,
    TURN_ON,
    MAX_EVENTS = 128,
    MAX_LIGHTS = 32
};

typedef enum Event
{
    E_EVENT_UNKNOWN,
    E_EVENT_TURN_ON,
    E_EVENT_TURN_OFF,
} E_EVENT_t;

typedef struct SchedulerLightEvent
{
    int8_t c_id;
    int32_t l_minuteOfDay;
    E_EVENT_t e_event;
    E_DAY_t e_day;
} SchedulerLightEvent;

static E_LS_T scheduleEvent(int id, E_DAY_t day, int minuteOfDay,
                          E_EVENT_t e_evt);
static void processEventDueNow(Time *ps_time,
                               SchedulerLightEvent *ps_lightEvent);
static void operateLight(SchedulerLightEvent *ps_lightEvent);
static bool doesLightRespondToday(Time *ps_time, E_DAY_t e_day);

SchedulerLightEvent gs_schedule;
SchedulerLightEvent gs_scheduleEvents[MAX_EVENTS];

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
    return scheduleEvent(id, day, minuteOfDay, E_EVENT_TURN_ON);
}

E_LS_T LightScheduler_ScheduleTurnOff(int id, E_DAY_t day, int minuteOfDay)
{
    return scheduleEvent(id, day, minuteOfDay, E_EVENT_TURN_OFF);
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
    
    return E_EVENT_UNKNOWN;
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

static E_LS_T scheduleEvent(int id, E_DAY_t day, int minuteOfDay, 
    E_EVENT_t e_evt)
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
            
            return E_LS_OK;
        }
    }

    return E_LS_TOO_MANY_EVENTS;
}

static void processEventDueNow(Time *ps_time,
                               SchedulerLightEvent *ps_lightEvent)
{
    if (ps_lightEvent->c_id == UNUSED)
        return;
    if (!doesLightRespondToday(ps_time, ps_lightEvent->e_day))
        return;
    if (ps_time->l_minuteOfDay != ps_lightEvent->l_minuteOfDay)
        return;

    operateLight(ps_lightEvent);
}

static void operateLight(SchedulerLightEvent *ps_lightEvent)
{
    if (E_EVENT_TURN_ON == ps_lightEvent->e_event)
    {
        LightController_On(ps_lightEvent->c_id);
    }
    else if (E_EVENT_TURN_OFF == ps_lightEvent->e_event)
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