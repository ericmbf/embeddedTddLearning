#include <stdbool.h>

#include "ledDriver.h"
#include "RuntimeError.h"

typedef enum E_LED_STATE
{
    E_LED_STATE_ALL_ON = ~0,
    E_LED_STATE_ALL_OFF = ~E_LED_STATE_ALL_ON,
} E_LED_STATE;

typedef enum E_LED_BOUND
{
    E_LED_BOUND_MIN = 0,
    E_LED_BOUND_MAX = 16,
} E_LED_BOUND;

static uint16_t convertLedNumberToBit(int ledNumber);
static void updateHardware(void);
static bool isValidLed(uint8_t uc_led);

static uint16_t *gpui_ledAddr;
static uint16_t guc_ledImage;

void LedDriver_Create(uint16_t * pui_address)
{
    gpui_ledAddr = pui_address;
    guc_ledImage = E_LED_STATE_ALL_OFF;
    updateHardware();
}

void LedDriver_Destroy(void)
{

}

void LedDriver_turnOn(uint8_t uc_led)
{   
    if(isValidLed(uc_led))
    {
        guc_ledImage |= convertLedNumberToBit(uc_led);
        updateHardware();
    }
}

void LedDriver_turnOff(uint8_t uc_led)
{
    if(isValidLed(uc_led))
    {
        guc_ledImage &= ~convertLedNumberToBit(uc_led);
        updateHardware();
    }
}

void LedDriver_turnAllOn(void)
{
    guc_ledImage = E_LED_STATE_ALL_ON;
    updateHardware();
}

bool LedDriver_isOn(uint8_t uc_led)
{
    if(!isValidLed(uc_led))
    {
        return false;
    }
    
    return guc_ledImage & (convertLedNumberToBit(uc_led));
}

bool LedDriver_isOff(uint8_t uc_led)
{
    if(!isValidLed(uc_led))
    {
        return false;
    }

    return !LedDriver_isOn(uc_led);
}

void LedDriver_turnAllOff(void)
{
    guc_ledImage = E_LED_STATE_ALL_OFF;
    updateHardware();
}


static uint16_t convertLedNumberToBit(int uc_led)
{
    return 1 << (uc_led - 1);
}

static void updateHardware(void)
{
    *gpui_ledAddr = ~guc_ledImage;
}

static bool isValidLed(uint8_t uc_led)
{
    bool b_ret = true;

    if(uc_led <= E_LED_BOUND_MIN || uc_led > E_LED_BOUND_MAX)
    {
        RUNTIME_ERROR("LED Driver: out-of-bounds LED", uc_led);
        b_ret = false;
    }

    return b_ret;
}