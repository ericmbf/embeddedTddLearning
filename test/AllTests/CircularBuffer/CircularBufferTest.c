#if UNIT_TEST
#include <unity.h>
#include <unity_fixture.h>

#include "CircularBuffer.h"

#define BUFFER_SIZE_TEST 10

static void putManyInTheBuffer(int seed, int howMany);

CircularBuffer buffer;

TEST_GROUP(CircularBuffer);

TEST_SETUP(CircularBuffer)
{
    buffer = CircularBuffer_Create(BUFFER_SIZE_TEST);
}

TEST_TEAR_DOWN(CircularBuffer)
{
    CircularBuffer_Destroy(buffer);
}

TEST(CircularBuffer, Create)
{

}

TEST(CircularBuffer, EmptyAfterCreation)
{
    TEST_ASSERT_TRUE(CircularBuffer_IsEmpty(buffer));
}

TEST(CircularBuffer, NotFullAfterCreation)
{
    TEST_ASSERT_FALSE(CircularBuffer_IsFull(buffer));
}

TEST(CircularBuffer, NotEmpty)
{
    CircularBuffer_Put(buffer, 10046);
    TEST_ASSERT_FALSE(CircularBuffer_IsEmpty(buffer));
}

TEST(CircularBuffer, NotEmptyThenEmpty)
{
    CircularBuffer_Put(buffer, 4567);
    TEST_ASSERT_FALSE(CircularBuffer_IsEmpty(buffer));
    CircularBuffer_Get(buffer);
    TEST_ASSERT_TRUE(CircularBuffer_IsEmpty(buffer));
}

TEST(CircularBuffer, GetPutOneValue)
{
    CircularBuffer_Put(buffer, 4567);
    TEST_ASSERT_EQUAL_INT(4567, CircularBuffer_Get(buffer));
}

TEST(CircularBuffer, GetPutAFew)
{
    CircularBuffer_Put(buffer, 1);
    CircularBuffer_Put(buffer, 2);
    CircularBuffer_Put(buffer, 3);
    TEST_ASSERT_EQUAL_INT(1, CircularBuffer_Get(buffer));
    TEST_ASSERT_EQUAL_INT(2, CircularBuffer_Get(buffer));
    TEST_ASSERT_EQUAL_INT(3, CircularBuffer_Get(buffer));
}

TEST(CircularBuffer, Capacity)
{
    CircularBuffer b = CircularBuffer_Create(2);
    TEST_ASSERT_EQUAL_INT(2, CircularBuffer_Capacity(b));
    CircularBuffer_Destroy(b);
}

TEST(CircularBuffer, IsFull)
{
    for (int i = 0; i < CircularBuffer_Capacity(buffer); i++)
        CircularBuffer_Put(buffer, i + 100);

    TEST_ASSERT_TRUE(CircularBuffer_IsFull(buffer));
}

TEST(CircularBuffer, EmptyToFullToEmpty)
{
    for (int i = 0; i < CircularBuffer_Capacity(buffer); i++)
        CircularBuffer_Put(buffer, i + 100);

    TEST_ASSERT_TRUE(CircularBuffer_IsFull(buffer));

    for (int j = 0; j < CircularBuffer_Capacity(buffer); j++)
        TEST_ASSERT_EQUAL_INT(j + 100, CircularBuffer_Get(buffer));

    TEST_ASSERT_TRUE(CircularBuffer_IsEmpty(buffer));
    TEST_ASSERT_FALSE(CircularBuffer_IsFull(buffer));
}

TEST(CircularBuffer, WrapAround)
{
    int capacity = CircularBuffer_Capacity(buffer);
    for (int i = 0; i < capacity; i++)
        CircularBuffer_Put(buffer, i + 100);

    TEST_ASSERT_TRUE(CircularBuffer_IsFull(buffer));
    TEST_ASSERT_EQUAL_INT(100, CircularBuffer_Get(buffer));
    TEST_ASSERT_FALSE(CircularBuffer_IsFull(buffer));
    CircularBuffer_Put(buffer, 1000);
    TEST_ASSERT_TRUE(CircularBuffer_IsFull(buffer));

    for (int j = 1; j < capacity; j++)
        TEST_ASSERT_EQUAL_INT(j + 100, CircularBuffer_Get(buffer));

    TEST_ASSERT_EQUAL_INT(1000, CircularBuffer_Get(buffer));
    TEST_ASSERT_TRUE(CircularBuffer_IsEmpty(buffer));
}

TEST(CircularBuffer, PutToFullThrows)
{
    putManyInTheBuffer(900, CircularBuffer_Capacity(buffer));
    TEST_ASSERT_FALSE(CircularBuffer_Put(buffer, 9999));
}

TEST(CircularBuffer, PutToFullDoesNotDamageContents)
{
    putManyInTheBuffer(900, CircularBuffer_Capacity(buffer));

    CircularBuffer_Put(buffer, 9999);

    for (int i = 0; i < CircularBuffer_Capacity(buffer); i++)
        TEST_ASSERT_EQUAL_INT(i + 900, CircularBuffer_Get(buffer));

    TEST_ASSERT_TRUE(CircularBuffer_IsEmpty(buffer));
}

TEST(CircularBuffer, GetFromEmptyReturns0)
{
    TEST_ASSERT_EQUAL_INT(0, CircularBuffer_Get(buffer));
}

static void putManyInTheBuffer(int seed, int howMany)
{
    for (int i = 0; i < howMany; i++)
        CircularBuffer_Put(buffer, i + seed);
}

#endif