
#include <stdint.h>
#include <stdbool.h>

void LedDriver_Create(uint16_t * ui_address, bool b_initZero, 
    bool b_invertedOrder);
void LedDriver_Destroy(void);
void LedDriver_turnOn(uint8_t uc_led);
void LedDriver_turnOff(uint8_t uc_led);
void LedDriver_turnAllOn(void);
bool LedDriver_isOn(uint8_t uc_led);
bool LedDriver_isOff(uint8_t uc_led);
void LedDriver_turnAllOff(void);