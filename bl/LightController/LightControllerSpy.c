#include <stdint.h>
#include "LightControllerSpy.h"
#include <string.h>

static int lastId;
static int lastState;

static int g_ledState[32];

void LightController_Create(void)
{
    lastId = LIGHT_ID_UNKNOWN;
    lastState = LIGHT_STATE_UNKNOWN;
    memset((void*)&g_ledState, LIGHT_STATE_UNKNOWN, sizeof(g_ledState));
}

void LightController_Destroy(void)
{

}

void LightController_On(int id)
{
    lastId = id;
    lastState = LIGHT_ON;
    g_ledState[id] = LIGHT_ON;
}

void LightController_Off(int id)
{
    lastId = id;
    lastState = LIGHT_OFF;
    g_ledState[id] = LIGHT_OFF;
}

int LightControllerSpy_GetLastId(void)
{
    return lastId;
}

int LightControllerSpy_GetLastState(void)
{
    return lastState;
}

int LightControllerSpy_GetLightState(int id)
{
    return g_ledState[id];
}
