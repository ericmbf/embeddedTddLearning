#include <stdint.h>
#include <string.h>
#include "LightController.h"
#include "LightDriver.h"

static LightDriver lightDrivers[MAX_LIGHTS] = {NULL};
static void destroy(LightDriver driver);

void LightController_Create(void)
{
    memset(lightDrivers, 0, sizeof lightDrivers);
}

void LightController_Destroy(void)
{
    int i;
    for (i = 0; i < MAX_LIGHTS; i++)
    {
        LightDriver driver = lightDrivers[i];
        destroy(driver);
        lightDrivers[i] = NULL;
    }
}

BOOL LightController_Add(int id, LightDriver lightDriver)
{
    if (id < 0 || id >= MAX_LIGHTS)
        return FALSE;

    destroy(lightDrivers[id]);

    lightDrivers[id] = lightDriver;
    return TRUE;
}

void LightController_TurnOn(int id)
{
    LightDriver driver = lightDrivers[id];
    if (NULL == driver)
        return;

#if 0
    switch (driver->type)
    {
    case X10:
        X10LightDriver_TurnOn(driver);
        break;
    case AcmeWireless:
        AcmeWirelessLightDriver_TurnOn(driver);
        break;
    case MemoryMapped:
        MemMappedLightDriver_TurnOn(driver);
        break;
    case TestLightDriver:
        LightDriverSpy_TurnOn(driver);
        break;
    default:
        /* now what? */
        break;
    }
#endif
}

void LightController_TurnOff(int id)
{
    LightDriver driver = lightDrivers[id];
    if (NULL == driver)
        return;

#if 0
    switch (driver->type)
    {
    case X10:
        X10LightDriver_TurnOff(driver);
        break;
    case AcmeWireless:
        AcmeWirelessLightDriver_TurnOff(driver);
        break;
    case MemoryMapped:
        MemMappedLightDriver_TurnOff(driver);
        break;
    case TestLightDriver:
        LightDriverSpy_TurnOff(driver);
        break;
    default:
        /* now what? */
        break;
    }
#endif
}

static void destroy(LightDriver driver)
{
    #if 0
    if (!driver)
        return;

    switch (driver->type)
    {
    case X10:
        X10LightDriver_Destroy(driver);
        break;
    case AcmeWireless:
        AcmeWirelessLightDriver_Destroy(driver);
        break;
    case MemoryMapped:
        MemMappedLightDriver_Destroy(driver);
        break;
    case TestLightDriver:
        LightDriverSpy_Destroy(driver);
        break;
    default:
        /* now what? */
        break;
    }
    #endif
}