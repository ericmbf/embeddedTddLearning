#if UNIT_TEST
#include "unity.h"
#include "unity_fixture.h"

TEST_GROUP_RUNNER(CircularBuffer)
{
    RUN_TEST_CASE(CircularBuffer, Create);
    RUN_TEST_CASE(CircularBuffer, insertNewValue);
    RUN_TEST_CASE(CircularBuffer, insertTwoValues);
    RUN_TEST_CASE(CircularBuffer, insertMoreThanSize);
    RUN_TEST_CASE(CircularBuffer, validPointerInit);
    RUN_TEST_CASE(CircularBuffer, insertAfterRemove);
    RUN_TEST_CASE(CircularBuffer, insertAfterFull);
    RUN_TEST_CASE(CircularBuffer, removeFifo);
}
#endif