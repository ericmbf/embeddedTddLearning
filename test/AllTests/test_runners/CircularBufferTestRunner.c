#if UNIT_TEST
#include "unity.h"
#include "unity_fixture.h"

TEST_GROUP_RUNNER(CircularBuffer)
{
    RUN_TEST_CASE(CircularBuffer, test_insertNewValue);
    RUN_TEST_CASE(CircularBuffer, test_insertTwoValues);
    RUN_TEST_CASE(CircularBuffer, test_insertMoreThanSize);
    RUN_TEST_CASE(CircularBuffer, test_validPointerInit);
    RUN_TEST_CASE(CircularBuffer, test_insertAfterRemove);
    RUN_TEST_CASE(CircularBuffer, test_insertAfterFull);
    RUN_TEST_CASE(CircularBuffer, test_removeFifo);
}
#endif