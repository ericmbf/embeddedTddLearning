#include <stdbool.h>

#include "LedDriver.h"
#include "RuntimeError.h"

typedef enum E_LED_STATE
{
    E_LED_STATE_ALL_ON = 0xFFFF,
    E_LED_STATE_ALL_OFF = (uint16_t) ~E_LED_STATE_ALL_ON,
} E_LED_STATE;

typedef enum E_LED_BOUND
{
    E_LED_BOUND_MIN = 0,
    E_LED_BOUND_MAX = 16,
} E_LED_BOUND;

static uint16_t convertLedNumberToBit(int32_t l_led);
static void updateHardware(void);
static bool isValidLed(int32_t l_led);
static uint16_t invertByteOrder(uint16_t ui_value);

static uint16_t *gpui_ledAddr;
static uint16_t guc_ledImage;
static bool gb_initZero;
static bool gb_invertedOrder;

void LedDriver_Create(uint16_t * pui_address, bool b_initZero, 
    bool b_invertedOrder)
{
    gpui_ledAddr = pui_address;
    gb_initZero = b_initZero;
    gb_invertedOrder = b_invertedOrder;

    guc_ledImage = E_LED_STATE_ALL_OFF;

    updateHardware();
}

void LedDriver_Destroy(void)
{

}

void LedDriver_turnOn(int32_t l_led)
{   
    if(isValidLed(l_led))
    {
        guc_ledImage |= convertLedNumberToBit(l_led);
        updateHardware();
    }
}

void LedDriver_turnOff(int32_t l_led)
{
    if(isValidLed(l_led))
    {
        guc_ledImage &= ~convertLedNumberToBit(l_led);
        updateHardware();
    }
}

void LedDriver_turnAllOn(void)
{
    guc_ledImage = E_LED_STATE_ALL_ON;
    updateHardware();
}

bool LedDriver_isOn(int32_t l_led)
{
    if(!isValidLed(l_led))
    {
        return false;
    }
    
    return guc_ledImage & (convertLedNumberToBit(l_led));
}

bool LedDriver_isOff(int32_t l_led)
{
    if(!isValidLed(l_led))
    {
        return false;
    }

    return !LedDriver_isOn(l_led);
}

void LedDriver_turnAllOff(void)
{
    guc_ledImage = E_LED_STATE_ALL_OFF;
    updateHardware();
}


static uint16_t convertLedNumberToBit(int32_t l_led)
{
    return 1 << (l_led - 1);
}

static void updateHardware(void)
{
    if(gb_invertedOrder & gb_initZero)
    {
        *gpui_ledAddr = invertByteOrder(guc_ledImage);
    }
    else if(gb_invertedOrder)
    {
        *gpui_ledAddr = invertByteOrder(~guc_ledImage);
    }
    else if(gb_initZero)
    {
        *gpui_ledAddr = ~guc_ledImage;
    }
    else
    {
        *gpui_ledAddr = guc_ledImage;
    }
}

static bool isValidLed(int32_t l_led)
{
    bool b_ret = true;

    if(l_led <= E_LED_BOUND_MIN || l_led > E_LED_BOUND_MAX)
    {
        RUNTIME_ERROR("LED Driver: out-of-bounds LED", l_led);
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