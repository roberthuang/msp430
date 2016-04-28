#include <msp430g2553.h>
#define Button BIT3
#define LED1 BIT0
#define LED2 BIT6
#define SET_BIT(x, y) ((x) = (x) | ((0)<<(y)))
#define SET(x, y) ((x) = (x) | ((1)<<(y)))

#define CLEAR(x, y) ((x) &= ~(1<<y))
/*
 * main.c
 */

void ConfigWDT(void);
void ConfigClocks(void);
void ConfigLEDs(void);
void ConfigTimerA(void);
void reset();

int main(void) {

	P1OUT = 0 | Button;
	P1DIR = LED2;
	P1REN = P1OUT;
	P1IE = Button;
    P1IES |= Button;
    P1IFG &= ~Button;
	ConfigWDT();
	ConfigClocks();
	ConfigTimerA();
	_enable_interrupt();
    for (;;) {
    }

}

void ConfigWDT() {
	WDTCTL = WDTPW | WDTHOLD;	// Stop watchdog timer
}

void ConfigClocks(void) {
    BCSCTL1 = CALBC1_1MHZ;
    DCOCTL = CALDCO_1MHZ;
    BCSCTL2 |=  DIVS_3;
    SET_BIT(BCSCTL2, 3);
}

void ConfigTimerA() {
	TACCR0 = 62499;
	TACTL = MC_3 | TASSEL_2;
    TACCTL0 = CCIE;
}

void ConfigLEDs(void) {
	P1OUT ^= LED2 + LED1;
}

void reset() {
	 TACTL = TACLR;
	 TACTL &= ~TAIFG;
}

#pragma vector = TIMER0_A0_VECTOR
__interrupt void TIMER0_A0_ISR (void){
    ConfigLEDs();
    TACTL &= ~TAIFG;
}

#pragma vector = PORT1_VECTOR
__interrupt void Port_1 (void) {
    P1DIR ^= LED1 + LED2;
	P1IFG &= ~Button;

}
