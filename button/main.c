#include <msp430g2553.h>
/*
 * main.c
 */
void main(void)
{
   WDTCTL = WDTPW + WDTHOLD;	        //關閉看門狗
   P1OUT = BIT3;            	        //設定PT1.3為高電位
   P1DIR = BIT0;            	        //設定PT1.0為輸出
   P1REN = P1OUT;           	        //設定PT1.3上拉電阻

   for ( ; ; ) {             	        //Polling Loop
   	if ((P1IN & BIT3) == 0) {
   		P1OUT ^= BIT0;
   		while ((P1IN & BIT3) == 0) {

   		}
   		P1OUT ^= BIT0;
   	}

   }

}
