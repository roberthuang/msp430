#include <msp430g2553.h>
long ADCDATA;
long tempInDeg;
/*
 * main.c
 */
int main(void) {

    WDTCTL = WDTPW | WDTHOLD;	// Stop watchdog timer
    ADC10CTL1 =  INCH_10+ SHS_1 + CONSEQ_2 ;
    ADC10CTL0 =  ADC10SHT_3 + ADC10ON + ADC10IE + REFON + SREF_1;

    __enable_interrupt();
    TACCR0 = 30;
    TACCTL0 |= CCIE;
    TACTL = TASSEL_2 + MC_1;
    LPM0;
    TACCTL0 &= ~CCIE;
    __disable_interrupt();


    P1DIR |= BIT0 + BIT6;
    P1OUT = BIT0;

    TACCR0 = 2048;
    TACCTL1 = OUTMOD_3;
    TACCR1 = 2047;
    TACTL =TASSEL_1 + MC_1;

    ADC10CTL0 |= ENC + ADC10SC;
    //Sleep
    __bis_SR_register(LPM3_bits + GIE); // Sleep


}

#pragma vector=ADC10_VECTOR
__interrupt void ADC10_ISR(void) {
	ADCDATA = ADC10MEM;
	tempInDeg = ((ADCDATA - 673) * 423) / 1024;
    if (tempInDeg > 32) {
    	 P1OUT |= BIT6;
    } else {
    	P1OUT &= ~BIT6;
    }
}

#pragma vector = TIMER0_A0_VECTOR
__interrupt void TIMER0_A0_ISR (void){
    TACTL = 0;
    LPM0_EXIT;
}
