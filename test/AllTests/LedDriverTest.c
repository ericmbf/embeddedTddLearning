#include <unity_fixture.h>
#include <unity.h>

#include "ledDriver.h"
#include "RuntimeErrorStub.h"

TEST_GROUP(LedDriver);

static uint16_t gui_virtualLeds;

TEST_SETUP(LedDriver)
{
    LedDriver_Create(&gui_virtualLeds);
}

TEST_TEAR_DOWN(LedDriver)
{
}

TEST(LedDriver, test_allLedOffsOnCreate)
{
    uint16_t uc_virtualLeds = 0;
    LedDriver_Create(&uc_virtualLeds);
    TEST_ASSERT_EQUAL(0xFFFF, uc_virtualLeds);
}

TEST(LedDriver, test_TurnOnLedOne)
{
    LedDriver_turnOn(1);
    TEST_ASSERT_EQUAL_HEX16(0x01, ~gui_virtualLeds);
}

TEST(LedDriver, test_TurnOffLedOne)
{
    LedDriver_turnOn(1);
    LedDriver_turnOff(1);
    TEST_ASSERT_EQUAL_HEX16(0x00, ~gui_virtualLeds);
}

TEST(LedDriver, test_TurnOnMultipleLeds)
{
    LedDriver_turnOn(1);
    LedDriver_turnOn(2);
    TEST_ASSERT_EQUAL_HEX16(0x03, ~gui_virtualLeds);
}

TEST(LedDriver, test_TurnOffAnyLed)
{
    LedDriver_turnAllOn();
    LedDriver_turnOff(2);
    TEST_ASSERT_EQUAL_HEX16(0xFFFD, ~gui_virtualLeds);
}

TEST(LedDriver, test_allOn)
{
    LedDriver_turnAllOn();
    TEST_ASSERT_EQUAL_HEX16(0xFFFF, ~gui_virtualLeds);
}

TEST(LedDriver, test_LedMemoryIsNotReadable)
{
    gui_virtualLeds = 0xFFFF;
    LedDriver_turnOn(8);
    TEST_ASSERT_EQUAL_HEX16(0x80, ~gui_virtualLeds);
}

TEST(LedDriver, test_UpperAndLowerBounds)
{
    LedDriver_turnOn(1);
    LedDriver_turnOn(16);
    TEST_ASSERT_EQUAL_HEX16(0x8001, ~gui_virtualLeds);
}

TEST(LedDriver, test_TurnOnOutOfBounds)
{
    LedDriver_turnOn(-1);
    TEST_ASSERT_EQUAL_HEX16(0, ~gui_virtualLeds);
    LedDriver_turnOn(0);
    TEST_ASSERT_EQUAL_HEX16(0, ~gui_virtualLeds);
    LedDriver_turnOn(17);
    TEST_ASSERT_EQUAL_HEX16(0, ~gui_virtualLeds);
    LedDriver_turnOn(3141);
    TEST_ASSERT_EQUAL_HEX16(0, ~gui_virtualLeds);
}

TEST(LedDriver, test_TurnOffOutOfBounds)
{
    LedDriver_turnAllOn();

    LedDriver_turnOff(-1);
    TEST_ASSERT_EQUAL_HEX16(0xFFFF, ~gui_virtualLeds);
    LedDriver_turnOff(0);
    TEST_ASSERT_EQUAL_HEX16(0xFFFF, ~gui_virtualLeds);
    LedDriver_turnOff(17);
    TEST_ASSERT_EQUAL_HEX16(0xFFFF, ~gui_virtualLeds);
    LedDriver_turnOff(3141);
    TEST_ASSERT_EQUAL_HEX16(0xFFFF, ~gui_virtualLeds);
}

TEST(LedDriver, test_OutOfBoundsProducesRuntimeError)
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

TEST(LedDriver, test_isOn)
{
    TEST_ASSERT_FALSE(LedDriver_isOn(2));
    LedDriver_turnOn(2);
    TEST_ASSERT_TRUE(LedDriver_isOn(2));
}

TEST(LedDriver, test_OutOfBoundsAreAlwaysOff)
{
    TEST_ASSERT_FALSE(LedDriver_isOff(0));
    TEST_ASSERT_FALSE(LedDriver_isOff(17));
    TEST_ASSERT_FALSE(LedDriver_isOn(0));
    TEST_ASSERT_FALSE(LedDriver_isOn(17));
}

TEST(LedDriver, test_isOff)
{
    TEST_ASSERT_TRUE(LedDriver_isOff(2));
    LedDriver_turnOn(2);
    TEST_ASSERT_FALSE(LedDriver_isOff(2));
}

TEST(LedDriver, test_TurnOffMultipleLeds)
{
    LedDriver_turnAllOn();
    LedDriver_turnOff(9);
    LedDriver_turnOff(8);
    TEST_ASSERT_EQUAL_HEX16((~0x180) & 0xFFFF, ~gui_virtualLeds);
}

TEST(LedDriver, test_AllOff)
{
    LedDriver_turnAllOn();
    LedDriver_turnAllOff();
    TEST_ASSERT_EQUAL_HEX16(0x00, ~gui_virtualLeds);
}