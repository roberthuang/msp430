#include <msp430g2553.h>
#define LED1 BIT0
#define LED2 BIT6
#define Button BIT3
#define SET_BIT(x, y) ((x) = (x) | ((0)<<(y)))

void change() {
	TACTL &= ~TAIFG;
	P1OUT ^= LED2;
}
void main(void) {
    WDTCTL = WDTPW + WDTHOLD;
    P1OUT = 0 | Button;
    P1DIR = LED2 + LED1;
    P1REN = P1OUT;
    //SET CLOCK
    BCSCTL1 = CALBC1_1MHZ;
    DCOCTL = CALDCO_1MHZ;
    BCSCTL2 |=  DIVS_3;
    SET_BIT(BCSCTL2, 3);
    //SET TIMER_A
    TACCR0 = 62499;
    TACTL = MC_3 | TASSEL_2;
    if ( CALBC1_1MHZ == 0xFF || CALDCO_1MHZ == 0xFF ) while (1);

    for (;;) {
    	if (TACTL&TAIFG) {
    	    change();
    	}
    	if ((P1IN & BIT3) == 0) {
    	    P1OUT ^= BIT0;
    	    if (TACTL&TAIFG) {
    	        change();
    	    }
    	    while ((P1IN & BIT3) == 0) {
    	    	if (TACTL&TAIFG) {
    	    	    change();
    	    	}
    	    }
    	    P1OUT ^= BIT0;
    	}

    }

} // main
