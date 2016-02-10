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
    NRST_GPS = 0;
    NRST_GPS_T = 0; // active le RST du GPS
    
    
    RST_RF =   0;     // mise de la partie RF en pause
    RST_RF_T = 0;
    CSN_RF =   1;
    CSN_RF_T = 0;
    
    Init_Clk();
    _NSTDIS = 0;        //  active l'interupt dans l'interupt
    AD1PCFGL = 0xFFFF;  // tout en numérique
    UART_PC_Init();
    Timer_Ms_Init();
    ADC_Init();
    I2C_Init();
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
            LED1 = !LED1;
            printf("%c\n",c);
            if (c == 'l') {
                for (j = 0; j< 101; j++) {
                    do { i++; } while (i); }
                LED1 = !LED1;
            } else if (c == '5') {
                i = ADC_Convert(ADC_CHAN_5V);
                printf("5V = %d 0x%04X\n", i, i);
            } else if (c == 'v') {
                i = ADC_Convert(ADC_CHAN_VBAT);
                printf("Vbat = %d 0x%04X\n", i, i);
            } else if (c == 'i') {
                I2C_Try();
            } else if (c == 'I') {
                I2C_Try_All();
            } else if (c == 'T') {
                test_transmit();
            } else if (c == 'e') {
                Alti_Read_EEPROM();
            } 
            else if (c == 'o') {
                GPS_Send_Off();
            } else if (c == 'g') {
                GPS_Send_On_Pin();
            } else if (c == 'G') {
                Get_Last_GPS_Messages();
            }  else if (c == 'q') {
                GPS_Querry_Message();
            } else if (c == 'f') {
                GPS_Go_Fast();
            } else if (c == 's') {
                GPS_Go_Slow();
            } else if (c == 't') {
                GPS_try_baudrates();
            } 
            /*
            else if (c == 'r') {
                RF_Reset();
            } else if (c == 'R') {
                RF_Read_All_Reg();
            } else if (c == 's') {
                RF_ON();
            } else if (c == 'S') {
                RF_Send_Packet();
            }  else if (c == 'W') {
                RF_Wait_For_Packet();
            }   else if (c == '?') {
                printf("RF Stat : 0x%02X\n", RF_Get_Status());
                printf("MODEM Stat 1 : 0x%02X\n", RF_Read_Reg(CC1120_MODEM_STATUS1));
                printf("MODEM Stat 0 : 0x%02X\n", RF_Read_Reg(CC1120_MODEM_STATUS1));
            } 
            */
            
        }
        if (Mode_Urgence) {
            GPS_Send_Off();
            while (1) {
            }
        }
        
    }
    
    
    
    return 0;
}
