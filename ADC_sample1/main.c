#include <msp430g2553.h>

/*
 * main.c
 */
int main(void) {
    WDTCTL = WDTPW | WDTHOLD;	// Stop watchdog timer
	ADC10CTL0 = ADC10SHT_2 + ADC10ON + ADC10IE;
    ADC10CTL1 = INCH_1;
    ADC10AE0 |= 0X02;
    P1DIR |= 0X01;
    for (;;) {
       ADC10CTL0 |= ENC + ADC10SC;
       __bits_SR_register(CPUOFF + GIE);//Interrupt�i��,�N���}Sleep
       if (ADC10MEM < 0X1FF) {
    	   P1OUT &= ~0X01;
       } else {
    	   P1OUT |= 0X01;
       }
    }
	return 0;
}
