/*
 * File:   main.c
 * Author: Pepino
 *
 * Created on 5 décembre 2015, 16:47
 */



#include "main.h"

volatile u8 Mode_Urgence = 0;

int main(void) {
    u16 i = 1;
    u8 j;
    char c;
    Init_Clk();
    _NSTDIS = 0;        //  active l'interupt dans l'interupt
    AD1PCFGL = 0xFFFF;  // tout en numérique
    UART_PC_Init();
    Timer_Ms_Init();
    ADC_Init();
    
    LED1_T = 0;
    LED2_T = 0;
    
    
    while (1) {
        if (Get_Uart(&c)) {
            LED1 = !LED1;
            Transmit_Char(c);
            if (c == 'l') {
                for (j = 0; j< 100; j++) {
                    do { i++; } while (i); }
                LED1 = !LED1;
            } else if (c == 't') {
                printf("toto %d\r\n", 0);
            } else if (c == '5') {
                i = ADC_Convert(ADC_CHAN_5V);
                printf("5V = %d %04X\r\n", i, i);
            } else if (c == 'v') {
                i = ADC_Convert(ADC_CHAN_VBAT);
                printf("Vbat = %d %04X\r\n", i, i);
            }
        }
        if (Mode_Urgence) {
            while (1) {
                LED1 = !LED1;
            }
        }
        
    }
    
    
    
    return 0;
}
