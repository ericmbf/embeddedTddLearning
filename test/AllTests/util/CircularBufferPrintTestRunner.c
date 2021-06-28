#if UNIT_TEST
#include "unity.h"
#include "unity_fixture.h"

TEST_GROUP_RUNNER(CircularBufferPrint)
{
    RUN_TEST_CASE(CircularBufferPrint, PrintEmpty);
    RUN_TEST_CASE(CircularBufferPrint, PrintAfterOneIsPut);
    RUN_TEST_CASE(CircularBufferPrint, PrintNotYetWrappedOrFull);
    RUN_TEST_CASE(CircularBufferPrint, PrintNotYetWrappedAndIsFull);
    RUN_TEST_CASE(CircularBufferPrint, PrintOldToNewWhenWrappedAndFull);
    RUN_TEST_CASE(CircularBufferPrint, PrintMultipliesLineLessthanFive);
    RUN_TEST_CASE(CircularBufferPrint, PrintMultipliesLineFullLine);
    RUN_TEST_CASE(CircularBufferPrint, PrintMultipliesLineOverFlowLine);
    RUN_TEST_CASE(CircularBufferPrint, PrintMultipliesLineMinWidthAllowed);
    RUN_TEST_CASE(CircularBufferPrint, PrintMultipliesLineCountWidth);
}
#endif