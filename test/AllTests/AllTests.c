#if UNIT_TEST
#include <unity.h>
#include <unity_fixture.h>

#if MSP430
#include <msp430.h>

static void halInit(void);
static void delay();
#endif

static void runAllTests(void)
{
    // RUN_TEST_GROUP(LedDriver);
    // RUN_TEST_GROUP(CircularBuffer);
    // RUN_TEST_GROUP(LightControllerSpy);
    // RUN_TEST_GROUP(FakeTimeService);
    // RUN_TEST_GROUP(LightScheduler);
    // RUN_TEST_GROUP(RandomMinute);
    // RUN_TEST_GROUP(FormatOutputSpy);
    // RUN_TEST_GROUP(CircularBufferPrint);
    // RUN_TEST_GROUP(Flash);
    // RUN_TEST_GROUP(FakeMicroTime);
    RUN_TEST_GROUP(LightController);
    RUN_TEST_GROUP(LightDriverSpy);
    RUN_TEST_GROUP(LightDriver);
}

int main(int argc, const char **argv)
{
#if MSP430
    halInit();
    
    // NOTE!!! Wait for >2 secs
    // if board doesn't support software reset via Serial.DTR/RTS
    delay();
    
    UnityMain(argc, argv, runAllTests);

    P4DIR |= 0x01; // Set P1.0 to output direction
    P4OUT ^= 0x01; // Toggle P4.0 using exclusive-OR
    return 0;
#else
    return UnityMain(argc, argv, runAllTests);
#endif

}

#if MSP430
static void halInit(void)
{
    WDTCTL = WDTPW | WDTHOLD;               // Stop watchdog timer
    PM5CTL0 &= ~LOCKLPM5; // Disable the GPIO power-on default high-impedance mode
}

static void delay()
{
    volatile unsigned long i; // volatile to prevent optimization

    i = 300000; // SW Delay
    do
        i--;
    while (i != 0);
}
#endif

#endif