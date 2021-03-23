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
static uint16_t invertByteOrder(uint16_t ui_value);

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
    *gpui_ledAddr = invertByteOrder(~guc_ledImage);
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

static uint16_t invertByteOrder(uint16_t ui_value)
{
    uint8_t uc_msb = (ui_value & 0xFF00) >> 8;   
    uint8_t uc_lsb = ui_value & 0x00FF;
    uint16_t ui_ret = 0;
      
    uc_msb = (uc_msb & 0xF0) >> 4 | (uc_msb & 0x0F) << 4;
    uc_msb = (uc_msb & 0xCC) >> 2 | (uc_msb & 0x33) << 2;
    uc_msb = (uc_msb & 0xAA) >> 1 | (uc_msb & 0x55) << 1;

    uc_lsb = (uc_lsb & 0xF0) >> 4 | (uc_lsb & 0x0F) << 4;
    uc_lsb = (uc_lsb & 0xCC) >> 2 | (uc_lsb & 0x33) << 2;
    uc_lsb = (uc_lsb & 0xAA) >> 1 | (uc_lsb & 0x55) << 1;

    ui_ret = ((uint16_t) uc_lsb << 8) | uc_msb;

    return ui_ret;
}