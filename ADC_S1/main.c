#include <msp430g2553.h>
long ADCDATA;
long tempInDeg;
/*
 * main.c
 */
int main(void) {
    WDTCTL = WDTPW | WDTHOLD;	// Stop watchdog timer
	ADC10CTL0 = ADC10SHT_3 + ADC10ON + ADC10IE + REFON + SREF_1;
    ADC10CTL1= INCH_10 + ADC10DIV_3;
    P1DIR |= BIT0 + BIT6;
    P1OUT = BIT0;
    __delay_cycles(30);
       for(;;) {
       ADC10CTL0 |= ENC + ADC10SC;
       __bis_SR_register(CPUOFF + GIE); // Sleep
       }

}

#pragma vector=ADC10_VECTOR
__interrupt void ADC10_ISR(void)
{
    __bic_SR_register_on_exit(CPUOFF);
  ADCDATA = ADC10MEM;
         // Temperature in degrees conversion by using formula ADCDATA = (1024*(Vtemp/Vref))
         tempInDeg = ((ADCDATA - 673) * 423) / 1024;
         if (tempInDeg > 32) {
      	   P1OUT |= BIT6;
         } else {
      	   P1OUT &= ~BIT6;
         }
}


