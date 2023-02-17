/*
 * File:   main.c
 * Author: Jacob t
 *
 * Created on February 16, 2023, 12:00 AM
 */

#include <xc.h>
#include <stdint.h>


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


#include <xc.h>
#include "display7segmentos.h"
#include "adclib.h"

unsigned char output, masked, digit0, digit1, digit0p, digit1p, digit_no, i, cnt;

void __interrupt() isr(void) {
    if (INTCONbits.RBIF == 1){
        if (PORTBbits.RB0 == 0) {cnt = cnt++;}
     if (PORTBbits.RB1 == 0) {cnt = cnt--;}
    INTCONbits.RBIF = 0;}
    else {
    if (digit_no == 0) { 
        PORTE = 0;
        PORTC = digit0;
        PORTE = 1;
        __delay_us(100);
        digit_no = 1; }
    else {
        PORTE = 0;
        PORTC = digit1;
        PORTE = 2;
        __delay_us(100);
        digit_no = 0; }
    TMR0 = 0;
    INTCONbits.T0IF = 0;
    }
}

void main(void) {
    cnt = 0;
    
    //Configurar tmr 0 y activar interrupcion
    OPTION_REG = 0x80;
    TMR0 = 0;
    INTCON = 0xE8;
    
    //Port E y C como output para controlar. 
    PORTE = 0;
    TRISE = 0;
    
    PORTC = 0;
    TRISC = 0;
    
    //Port B y D como input y output para mostrar y controlar contador
    TRISB = 0x03;
    PORTB = 0;
    IOCB = 0x03;
    
    TRISD = 0;
    PORTD = 0;
    
    digit_no = 1;
    
    //Prepare el puerto 7 para utilizarlo para la alarma
    TRISAbits.TRISA7 = 0;
    PORTAbits.RA7 = 0;
    
    //Configurar ADC y port A
    char ch = 0;
    adc_setup(0);  
    adc_channel(ch);
    
    do {       
        __delay_us(50);
        output = adc_RO(ch);
        masked = mask(output);
        digit0p = output % 0x10;
        digit1p = output / 0x10;
        digit0 = mask(digit0p);
        digit1 = mask(digit1p);
        //PORTD = cnt; //Despliegue el contador en la puerta b
        //Controla la alarma 
        if (output > cnt) {PORTAbits.RA7 = 1;} else {PORTAbits.RA7 = 0;}
        PORTD = cnt; 
    } while (1);
}
