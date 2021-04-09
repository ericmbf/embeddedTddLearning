#if UNIT_TEST
#include "unity.h"
#include "unity_fixture.h"

TEST_GROUP_RUNNER(CircularBuffer)
{
    RUN_TEST_CASE(CircularBuffer, Create);
    RUN_TEST_CASE(CircularBuffer, EmptyAfterCreation);
    RUN_TEST_CASE(CircularBuffer, NotFullAfterCreation);
    RUN_TEST_CASE(CircularBuffer, NotEmpty);
    RUN_TEST_CASE(CircularBuffer, NotEmptyThenEmpty);
    RUN_TEST_CASE(CircularBuffer, GetPutOneValue);
    RUN_TEST_CASE(CircularBuffer, GetPutAFew);
    RUN_TEST_CASE(CircularBuffer, Capacity);
    RUN_TEST_CASE(CircularBuffer, IsFull);
    RUN_TEST_CASE(CircularBuffer, EmptyToFullToEmpty);
    RUN_TEST_CASE(CircularBuffer, WrapAround);
    RUN_TEST_CASE(CircularBuffer, PutToFullThrows);
    RUN_TEST_CASE(CircularBuffer, PutToFullDoesNotDamageContents);
    RUN_TEST_CASE(CircularBuffer, GetFromEmptyReturns0);
}
#endif