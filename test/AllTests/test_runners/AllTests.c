#include <unity.h>
#include <unity_fixture.h>

static void runAllTests(void)
{
    RUN_TEST_GROUP(LedDriver);
    RUN_TEST_GROUP(CircularBuffer);
}

int main(int argc, const char **argv)
{
    return UnityMain(argc, argv, runAllTests);
}