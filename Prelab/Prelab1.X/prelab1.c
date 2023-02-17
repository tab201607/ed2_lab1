/*
 * File:   counter_8bit.c
 * Author: JT
 *
 * Created on February 9, 2023, 10:16 PM
 */


#include <xc.h>
#pragma config FOSC = INTRC_NOCLKOUT        // Oscillator Selection bits (XT oscillator: Crystal/resonator on RA6/OSC2/CLKOUT and RA7/OSC1/CLKIN)
#pragma config WDTE = OFF       // Watchdog Timer Enable bit (WDT disabled and can be enabled by SWDTEN bit of the WDTCON register)
#pragma config PWRTE = OFF      // Power-up Timer Enable bit (PWRT disabled)
#pragma config MCLRE = OFF       // RE3/MCLR pin function select bit (RE3/MCLR pin function is MCLR)
#pragma config CP = OFF         // Code Protection bit (Program memory code protection is disabled)
#pragma config CPD = OFF        // Data Code Protection bit (Data memory code protection is disabled)
#pragma config BOREN = OFF       // Brown Out Reset Selection bits (BOR enabled)
#pragma config IESO = OFF        // Internal External Switchover bit (Internal/External Switchover mode is enabled)
#pragma config FCMEN = OFF       // Fail-Safe Clock Monitor Enabled bit (Fail-Safe Clock Monitor is enabled)
#pragma config LVP = OFF         // Low Voltage Programming Enable bit (RB3/PGM pin has PGM function, low voltage programming enabled)

// CONFIG2
#pragma config BOR4V = BOR40V   // Brown-out Reset Selection bit (Brown-out Reset set to 4.0V)
#pragma config WRT = OFF        // Flash Program Memory Self Write Enable bits (Write protection off)




#include <stdint.h>
#define _XTAL_FREQ 4000000



char cnt; 

void __interrupt() isr(void) {
     if (PORTBbits.RB0 == 0) cnt = cnt++;
     if (PORTBbits.RB1 == 0) cnt = cnt--;
    INTCONbits.RBIF = 0;
    //while (PORTBbits.RB0 == 1 || PORTBbits.RB1 == 1);
}

void main(void) {
    cnt = 0;
    ANSEL = 0;
    ANSELH = 0;
    TRISB = 0x03;
    PORTB = 0x00;
    TRISC = 0x00;
    PORTC = 0x00;
    INTCON = 0x88;
    IOCB = 0xFF;
    //OPTION_REG = 0x80;
    while(1) {
    PORTC = cnt;}
}
