#include <msp430g2553.h>
/*
 * main.c
 */
void main(void)
{
   WDTCTL = WDTPW + WDTHOLD;	        //�����ݪ���
   P1OUT = BIT3;            	        //�]�wPT1.3�����q��
   P1DIR = BIT0;            	        //�]�wPT1.0����X
   P1REN = P1OUT;           	        //�]�wPT1.3�W�Թq��

   for ( ; ; ) {             	        //Polling Loop
   	if ((P1IN & BIT3) == 0) {
   		P1OUT ^= BIT0;
   		while ((P1IN & BIT3) == 0) {

   		}
   		P1OUT ^= BIT0;
   	}

   }

}