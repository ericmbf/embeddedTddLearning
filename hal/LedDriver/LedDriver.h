
#include <stdint.h>
#include <stdbool.h>

void LedDriver_Create(uint16_t * ui_address, bool b_initZero, 
    bool b_invertedOrder);
void LedDriver_Destroy(void);
void LedDriver_turnOn(int32_t l_led);
void LedDriver_turnOff(int32_t l_led);
void LedDriver_turnAllOn(void);
bool LedDriver_isOn(int32_t l_led);
bool LedDriver_isOff(int32_t l_led);
void LedDriver_turnAllOff(void);