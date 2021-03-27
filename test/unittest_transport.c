#if defined(UNIT_TEST) && defined(MSP430)

#include "unittest_transport.h"

#include <stdint.h>
#include "eusci_a_uart.h"
#include "msp430fr4133.h"

static void initEusci(void);

void unittest_uart_begin()
{
    initEusci();
}

void unittest_uart_putchar(char c)
{
    // Transmit Character
    while (EUSCI_A_UART_queryStatusFlags(EUSCI_A0_BASE, EUSCI_A_UART_BUSY));
    EUSCI_A_UART_transmitData(EUSCI_A0_BASE, c);
}

void unittest_uart_flush()
{
}

void unittest_uart_end()
{
}

// EUSCI 0
static void initEusci(void)
{
    PM5CTL0 &= ~LOCKLPM5; // Disable the GPIO power-on default high-impedance mode
    // to activate previously configured port settings
    // Configure UART pins
    P1SEL0 |= BIT0 | BIT1; // set 2-UART pin as second function

    // Configure UART
    UCA0CTLW0 |= UCSWRST; // Put eUSCI in reset
    UCA0CTLW0 |= UCSSEL__SMCLK;
    // Baud Rate calculation
    UCA0BR0 = 8;        // 1000000/115200 = 8.68
    UCA0MCTLW = 0xD600; // 1000000/115200 - INT(1000000/115200)=0.68
    // UCBRSx value = 0xD6 (See UG)
    UCA0BR1 = 0;
    UCA0CTLW0 &= ~UCSWRST; // Initialize eUSCI
    UCA0IE |= UCRXIE;      // Enable USCI_A0 RX interrupt
}

#endif