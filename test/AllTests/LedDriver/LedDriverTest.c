#if UNIT_TEST
#include <unity_fixture.h>
#include <unity.h>

#include "LedDriver.h"
#include "RuntimeErrorStub.h"
#include "LedDriverTest.h"

#if UNIT_TEST && MSP430
#include "msp430.h"
#endif

TEST_GROUP(LedDriver);

static uint16_t invertByteOrder(uint16_t uc_value);
static uint16_t getExpected(uint16_t ui_expected);

static uint16_t gui_virtualLeds;
static bool gb_initZero = true;
static bool gb_invertedOrder = false;

TEST_SETUP(LedDriver)
{
    LedDriver_Create(&gui_virtualLeds, gb_initZero, gb_invertedOrder);
}

TEST_TEAR_DOWN(LedDriver)
{
}

TEST(LedDriver, allLedOffsOnCreate)
{
    uint16_t uc_virtualLeds = gb_initZero ? 0xFFFF : 0x0000;
    LedDriver_Create(&uc_virtualLeds, gb_initZero, gb_invertedOrder);
    TEST_ASSERT_EQUAL(getExpected(0), uc_virtualLeds);
}

TEST(LedDriver, TurnOnLedOne)
{
    LedDriver_turnOn(1);
    TEST_ASSERT_EQUAL_HEX16(getExpected(0x01), gui_virtualLeds);
}

TEST(LedDriver, TurnOffLedOne)
{
    LedDriver_turnOn(1);
    LedDriver_turnOff(1);
    TEST_ASSERT_EQUAL_HEX16(getExpected(0x00), gui_virtualLeds);
}

TEST(LedDriver, TurnOnMultipleLeds)
{
    LedDriver_turnOn(1);
    LedDriver_turnOn(2);
    TEST_ASSERT_EQUAL_HEX16(getExpected(0x03), gui_virtualLeds);
}

TEST(LedDriver, TurnOffAnyLed)
{
    LedDriver_turnAllOn();
    LedDriver_turnOff(2);
    TEST_ASSERT_EQUAL_HEX16(getExpected(0xFFFD), gui_virtualLeds);
}

TEST(LedDriver, allOn)
{
    LedDriver_turnAllOn();
    TEST_ASSERT_EQUAL_HEX16(getExpected(0xFFFF), gui_virtualLeds);
}

TEST(LedDriver, LedMemoryIsNotReadable)
{
    gui_virtualLeds = 0xFFFF;
    LedDriver_turnOn(8);
    TEST_ASSERT_EQUAL_HEX16(getExpected(0x80), gui_virtualLeds);
}

TEST(LedDriver, UpperAndLowerBounds)
{
    LedDriver_turnOn(1);
    LedDriver_turnOn(16);
    TEST_ASSERT_EQUAL_HEX16(getExpected(0x8001), gui_virtualLeds);
}

TEST(LedDriver, TurnOnOutOfBounds)
{
    LedDriver_turnOn(-1);
    TEST_ASSERT_EQUAL_HEX16(getExpected(0), gui_virtualLeds);
    LedDriver_turnOn(0);
    TEST_ASSERT_EQUAL_HEX16(getExpected(0), gui_virtualLeds);
    LedDriver_turnOn(17);
    TEST_ASSERT_EQUAL_HEX16(getExpected(0), gui_virtualLeds);
    LedDriver_turnOn(3141);
    TEST_ASSERT_EQUAL_HEX16(getExpected(0), gui_virtualLeds);
}

TEST(LedDriver, TurnOffOutOfBounds)
{
    LedDriver_turnAllOn();

    LedDriver_turnOff(-1);
    TEST_ASSERT_EQUAL_HEX16(getExpected(0xFFFF), gui_virtualLeds);
    LedDriver_turnOff(0);
    TEST_ASSERT_EQUAL_HEX16(getExpected(0xFFFF), gui_virtualLeds);
    LedDriver_turnOff(17);
    TEST_ASSERT_EQUAL_HEX16(getExpected(0xFFFF), gui_virtualLeds);
    LedDriver_turnOff(3141);
    TEST_ASSERT_EQUAL_HEX16(getExpected(0xFFFF), gui_virtualLeds);
}

TEST(LedDriver, OutOfBoundsProducesRuntimeError)
{
    LedDriver_turnOn(-1);
    TEST_ASSERT_EQUAL_STRING("LED Driver: out-of-bounds LED",
        RuntimeErrorStub_GetLastError());
    TEST_ASSERT_EQUAL(255, RuntimeErrorStub_GetLastParameter());
}

IGNORE_TEST(LedDriver, OutOfBoundsToDo)
{
    /* TODO: test */
}

TEST(LedDriver, isOn)
{
    TEST_ASSERT_FALSE(LedDriver_isOn(2));
    LedDriver_turnOn(2);
    TEST_ASSERT_TRUE(LedDriver_isOn(2));
}

TEST(LedDriver, OutOfBoundsAreAlwaysOff)
{
    TEST_ASSERT_FALSE(LedDriver_isOff(0));
    TEST_ASSERT_FALSE(LedDriver_isOff(17));
    TEST_ASSERT_FALSE(LedDriver_isOn(0));
    TEST_ASSERT_FALSE(LedDriver_isOn(17));
}

TEST(LedDriver, isOff)
{
    TEST_ASSERT_TRUE(LedDriver_isOff(2));
    LedDriver_turnOn(2);
    TEST_ASSERT_FALSE(LedDriver_isOff(2));
}

TEST(LedDriver, TurnOffMultipleLeds)
{
    LedDriver_turnAllOn();
    LedDriver_turnOff(9);
    LedDriver_turnOff(8);
    TEST_ASSERT_EQUAL_HEX16(getExpected((~0x180) & 0xFFFF), gui_virtualLeds);
}

TEST(LedDriver, AllOff)
{
    LedDriver_turnAllOn();
    LedDriver_turnAllOff();
    TEST_ASSERT_EQUAL_HEX16(getExpected(0x00), gui_virtualLeds);
}

#if UNIT_TEST && MSP430
TEST(LedDriver, ledTurnOnHardware)
{
    P4DIR |= 0x01; // Set P1.0 to output direction
    gui_virtualLeds = P4OUT;
    gb_initZero = false;
    gb_invertedOrder = false;
    LedDriver_Create(&gui_virtualLeds, gb_initZero, gb_invertedOrder);
    LedDriver_turnOn(1);
    TEST_ASSERT_EQUAL_HEX16(getExpected(0x01), gui_virtualLeds);
    TEST_MESSAGE("LED P4.0 should be turn on on the EVM.");
}
#endif

void LedDriverTest_setParam(bool b_initZero, bool b_invertedOrder)
{
    gb_initZero = b_initZero;
    gb_invertedOrder = b_invertedOrder;
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

static uint16_t getExpected(uint16_t ui_expected)
{
    uint16_t ui_ret = 0;

    if(gb_initZero && gb_invertedOrder)
    {
        ui_ret = invertByteOrder(ui_expected);
    }
    else if(gb_invertedOrder)
    {
        ui_ret = invertByteOrder(~ui_expected);
    }
    else if(gb_initZero)
    {
        ui_ret = ~ui_expected;
    }
    else
    {
        ui_ret = ui_expected;
    }

    return ui_ret;
}
#endif