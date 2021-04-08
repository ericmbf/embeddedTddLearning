#if UNIT_TEST
#include "unity.h"
#include "unity_fixture.h"

#include "LedDriverTest.h"

TEST_GROUP_RUNNER(LedDriver)
{
    LedDriverTest_setParam(true, false);
    RUN_TEST_CASE(LedDriver, allLedOffsOnCreate);
    RUN_TEST_CASE(LedDriver, TurnOnLedOne);
    RUN_TEST_CASE(LedDriver, TurnOffLedOne);
    RUN_TEST_CASE(LedDriver, TurnOnMultipleLeds);
    RUN_TEST_CASE(LedDriver, TurnOffAnyLed);
    RUN_TEST_CASE(LedDriver, allOn);
    RUN_TEST_CASE(LedDriver, LedMemoryIsNotReadable);
    RUN_TEST_CASE(LedDriver, UpperAndLowerBounds);
    RUN_TEST_CASE(LedDriver, TurnOnOutOfBounds);
    RUN_TEST_CASE(LedDriver, TurnOffOutOfBounds);
    RUN_TEST_CASE(LedDriver, OutOfBoundsProducesRuntimeError);
    RUN_TEST_CASE(LedDriver, OutOfBoundsToDo);
    RUN_TEST_CASE(LedDriver, isOn);
    RUN_TEST_CASE(LedDriver, OutOfBoundsAreAlwaysOff);
    RUN_TEST_CASE(LedDriver, isOff);
    RUN_TEST_CASE(LedDriver, TurnOffMultipleLeds);
    RUN_TEST_CASE(LedDriver, AllOff);
    
    LedDriverTest_setParam(false, false);
    RUN_TEST_CASE(LedDriver, allLedOffsOnCreate);
    RUN_TEST_CASE(LedDriver, TurnOnLedOne);
    RUN_TEST_CASE(LedDriver, TurnOffLedOne);
    RUN_TEST_CASE(LedDriver, TurnOnMultipleLeds);
    RUN_TEST_CASE(LedDriver, TurnOffAnyLed);
    RUN_TEST_CASE(LedDriver, allOn);
    RUN_TEST_CASE(LedDriver, LedMemoryIsNotReadable);
    RUN_TEST_CASE(LedDriver, UpperAndLowerBounds);
    RUN_TEST_CASE(LedDriver, TurnOnOutOfBounds);
    RUN_TEST_CASE(LedDriver, TurnOffOutOfBounds);
    RUN_TEST_CASE(LedDriver, OutOfBoundsProducesRuntimeError);
    RUN_TEST_CASE(LedDriver, OutOfBoundsToDo);
    RUN_TEST_CASE(LedDriver, isOn);
    RUN_TEST_CASE(LedDriver, OutOfBoundsAreAlwaysOff);
    RUN_TEST_CASE(LedDriver, isOff);
    RUN_TEST_CASE(LedDriver, TurnOffMultipleLeds);
    RUN_TEST_CASE(LedDriver, AllOff);

    LedDriverTest_setParam(true, true);
    RUN_TEST_CASE(LedDriver, allLedOffsOnCreate);
    RUN_TEST_CASE(LedDriver, TurnOnLedOne);
    RUN_TEST_CASE(LedDriver, TurnOffLedOne);
    RUN_TEST_CASE(LedDriver, TurnOnMultipleLeds);
    RUN_TEST_CASE(LedDriver, TurnOffAnyLed);
    RUN_TEST_CASE(LedDriver, allOn);
    RUN_TEST_CASE(LedDriver, LedMemoryIsNotReadable);
    RUN_TEST_CASE(LedDriver, UpperAndLowerBounds);
    RUN_TEST_CASE(LedDriver, TurnOnOutOfBounds);
    RUN_TEST_CASE(LedDriver, TurnOffOutOfBounds);
    RUN_TEST_CASE(LedDriver, OutOfBoundsProducesRuntimeError);
    RUN_TEST_CASE(LedDriver, OutOfBoundsToDo);
    RUN_TEST_CASE(LedDriver, isOn);
    RUN_TEST_CASE(LedDriver, OutOfBoundsAreAlwaysOff);
    RUN_TEST_CASE(LedDriver, isOff);
    RUN_TEST_CASE(LedDriver, TurnOffMultipleLeds);
    RUN_TEST_CASE(LedDriver, AllOff);

#if MSP430
    RUN_TEST_CASE(LedDriver, ledTurnOnHardware);
#endif
}
#endif