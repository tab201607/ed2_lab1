/*
 * File:   adc.c
 * Author: Jacob T
 *
 * Created on February 10, 2023, 3:19 AM
 */


#include <xc.h>
#include <stdint.h>
#include "adclib.h"

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

#define testbit(var, bit) ((var) & (1 << (bit)))
#define setbit(var, bit) ((var) |= (1 << (bit)))
#define clrbit(var, bit) ((var) &= ~(1 << (bit)))


void main(void) {
    char ch;
    TRISC = 0x00;
    PORTC = 0;
    ch = 0;
    adc_setup();  
    adc_channel(ch);
    while (1) {
        __delay_us(50);
        adc_read(ch);
    }
}
    

void __interrupt() isr(void) {
    PORTC = adc_output();
}

// Codigo sin librerias
/*void main(void) {
    
    ANSEL = 0x01; //AN0 y AN11
    ANSELH = 0x00;
    
    TRISA = 0x01;
    PORTA = 0x00;
    TRISC = 0x00;
    PORTC = 0x00;
    
    PIE1 = 0b01000000; //activa adc interrupt
    
    
    INTCON = 0xC0;
    ADCON1bits.ADFM = 0; 
    ADCON1bits.VCFG0 = 0;
    ADCON1bits.VCFG1 = 0;
    
    ADCON0bits.ADCS = 1; 
    ADCON0bits.CHS = 0;  
    __delay_us(100);
    ADCON0bits.ADON = 1;  
    __delay_us(100);
    
    while(1) {
    if (ADCON0bits.GO == 0){
            __delay_us(50);
            ADCON0bits.GO = 1;
        }
    };
}

void __interrupt() isr(void) {
    PIR1 = 0x00;
    PORTC = ADRESH;
}

*/


