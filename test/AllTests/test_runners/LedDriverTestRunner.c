#include "unity.h"
#include "unity_fixture.h"

TEST_GROUP_RUNNER(LedDriver)
{
    RUN_TEST_CASE(LedDriver, test_allLedOffsOnCreate);
    RUN_TEST_CASE(LedDriver, test_TurnOnLedOne);
    RUN_TEST_CASE(LedDriver, test_TurnOffLedOne);
    RUN_TEST_CASE(LedDriver, test_TurnOnMultipleLeds);
    RUN_TEST_CASE(LedDriver, test_TurnOffAnyLed);
    RUN_TEST_CASE(LedDriver, test_allOn);
    RUN_TEST_CASE(LedDriver, test_LedMemoryIsNotReadable);
    RUN_TEST_CASE(LedDriver, test_UpperAndLowerBounds);
    RUN_TEST_CASE(LedDriver, test_TurnOnOutOfBounds);
    RUN_TEST_CASE(LedDriver, test_TurnOffOutOfBounds);
    RUN_TEST_CASE(LedDriver, test_OutOfBoundsProducesRuntimeError);
    RUN_TEST_CASE(LedDriver, OutOfBoundsToDo);
    RUN_TEST_CASE(LedDriver, test_isOn);
    RUN_TEST_CASE(LedDriver, test_OutOfBoundsAreAlwaysOff);
    RUN_TEST_CASE(LedDriver, test_isOff);
    RUN_TEST_CASE(LedDriver, test_TurnOffMultipleLeds);
    RUN_TEST_CASE(LedDriver, test_AllOff);
}