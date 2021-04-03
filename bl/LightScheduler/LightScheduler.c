#include "LightScheduler.h"
#include "TimeService.h"
#include "LightControllerSpy.h"

enum
{
    UNUSED = -1,
    TURN_OFF,
    TURN_ON,
    MAX_EVENTS = 128
};

typedef struct LightSchedulerEvent
{
    int8_t c_id;
    int8_t c_minuteOfDay;
} LightSchedulerEvent;

LightSchedulerEvent gs_schedule;

void LightScheduler_Create()
{
    gs_schedule.c_id = UNUSED;
}

void LightScheduler_Destroy()
{

}

void LightScheduler_ScheduleTurnOn(int id, Day day, int minuteOfDay)
{
    gs_schedule.c_id = id;
    gs_schedule.c_minuteOfDay = minuteOfDay;
}

void LightScheduler_WakeUp()
{
    Time time;
    TimeService_GetTime(&time);

    if(gs_schedule.c_id == UNUSED)
        return;
    if(time.minuteOfDay != gs_schedule.c_minuteOfDay)
        return;
    
    LightController_On(gs_schedule.c_id);
}
