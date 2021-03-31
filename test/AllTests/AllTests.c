#if UNIT_TEST
#include <unity.h>
#include <unity_fixture.h>

#if MSP430
#include <msp430.h>
#endif

static void halInit(void);
static void delay();

static void runAllTests(void)
{
    RUN_TEST_GROUP(LedDriver);
    RUN_TEST_GROUP(CircularBuffer);
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