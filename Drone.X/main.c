/*
 * File:   main.c
 * Author: Pepino
 *
 * Created on 5 d�cembre 2015, 16:47
 */



#include "main.h"

volatile u8 Mode_Urgence = 0;

int main(void) {
    u8 c;
    NRST_GPS = 0;
    NRST_GPS_T = 0; // active le RST du GPS
    
    
    RST_RF =   0;     // mise de la partie RF en pause
    RST_RF_T = 0;
    CSN_RF =   1;
    CSN_RF_T = 0;
    
    Init_Clk();
    _NSTDIS = 0;        //  active l'interupt dans l'interupt
    AD1PCFGL = 0xFFFF;  // tout en num�rique
    UART_PC_Init();
    Timer_Ms_Init();
    ADC_Init();
    I2C_Init();
    //Accel_Init();
    SPI_Init();
    
    
    LED1_T = 0;
    LED2_T = 0;
    ON_OFF_GPS = 0;
    ON_OFF_GPS_T = 0;   // active la sortie ON_OFF du GPS
    Delay_ms(50);
    UART_GPS_Init();
    
    
    Delay_ms(500);
    printf("Running!\n");
    while (1) {
        if (Get_Uart(&c)) {
            LED1 = 1;
            Interp(c);
            LED1 = 0;
        }
        if (Mode_Urgence) {
            GPS_Send_Off_Cmd();
        }
        Accel_Loop();
    }
    
    return 0;
}
