#if UNIT_TEST
#include <unity.h>
#include <unity_fixture.h>

#include "CircularBuffer.h"

#define BUFFER_SIZE_TEST 10

int32_t gl_arrayBuffer[BUFFER_SIZE_TEST];
int32_t gl_popValue = 0;

TEST_GROUP(CircularBuffer);

TEST_SETUP(CircularBuffer)
{
    CircularBuffer_init((uint8_t *)&gl_arrayBuffer, BUFFER_SIZE_TEST);
}

TEST_TEAR_DOWN(CircularBuffer)
{
}

TEST(CircularBuffer, test_insertNewValue)
{
    CircularBuffer_insert(10);
    CircularBuffer_remove(&gl_popValue);
    TEST_ASSERT_EQUAL_INT32(10, gl_popValue);
}

TEST(CircularBuffer, test_insertTwoValues)
{
    CircularBuffer_insert(10);
    CircularBuffer_insert(20);
    CircularBuffer_remove(&gl_popValue);
    TEST_ASSERT_EQUAL_INT32(10, gl_popValue);
    CircularBuffer_remove(&gl_popValue);
    TEST_ASSERT_EQUAL_INT32(20, gl_popValue);
}

TEST(CircularBuffer, test_insertMoreThanSize)
{
    CircularBuffer_init((uint8_t*) &gl_arrayBuffer, 1);
    TEST_ASSERT_TRUE(CircularBuffer_insert(10));
    TEST_ASSERT_FALSE(CircularBuffer_insert(20));
}

TEST(CircularBuffer, test_validPointerInit)
{
    CircularBuffer_init((uint8_t*) &gl_arrayBuffer, 1);

    CircularBuffer_insert(10);
    TEST_ASSERT_EQUAL_INT32(10, gl_arrayBuffer[0]);
}

TEST(CircularBuffer, test_insertAfterRemove)
{
    CircularBuffer_insert(10);
    CircularBuffer_insert(20);
    CircularBuffer_remove(&gl_popValue);
    TEST_ASSERT_TRUE(CircularBuffer_insert(30));
}

TEST(CircularBuffer, test_insertAfterFull)
{
    int32_t l_expectedArray1[] = {40, 50, 30};
    CircularBuffer_init((uint8_t *)&gl_arrayBuffer, 3);
    CircularBuffer_insert(10);
    CircularBuffer_insert(20);
    CircularBuffer_insert(30);
    CircularBuffer_remove(&gl_popValue);
    CircularBuffer_insert(40);
    CircularBuffer_remove(&gl_popValue);
    CircularBuffer_insert(50);
    TEST_ASSERT_EQUAL_INT32_ARRAY(&l_expectedArray1, &gl_arrayBuffer, 3);
}

TEST(CircularBuffer, test_removeFifo)
{
    CircularBuffer_init((uint8_t *)&gl_arrayBuffer, 3);
    CircularBuffer_insert(10);
    CircularBuffer_insert(20);
    CircularBuffer_insert(30);
    CircularBuffer_remove(&gl_popValue);
    TEST_ASSERT_EQUAL_INT32(10, gl_popValue);
    CircularBuffer_insert(40);
    CircularBuffer_remove(&gl_popValue);
    TEST_ASSERT_EQUAL_INT32(20, gl_popValue);
    CircularBuffer_insert(50);
    CircularBuffer_remove(&gl_popValue);
    TEST_ASSERT_EQUAL_INT32(30, gl_popValue);
    CircularBuffer_remove(&gl_popValue);
    TEST_ASSERT_EQUAL_INT32(40, gl_popValue);
    CircularBuffer_remove(&gl_popValue);
    TEST_ASSERT_EQUAL_INT32(50, gl_popValue);
}

TEST(CircularBuffer, test_removeEmpty)
{
    TEST_ASSERT_FALSE(CircularBuffer_remove(&gl_popValue));
}
#endif