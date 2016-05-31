
#ifndef __MAIN_H
#define	__MAIN_H

#include <xc.h>

#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>

typedef uint32_t u32;
typedef uint16_t u16;
typedef uint8_t u8;

#define FOSC 80017143    // Freq de l'horloge après la PLL (avec M à 152)
//#define FOSC 79490714    // Freq de l'horloge après la PLL (avec M à 151)
//#define FOSC 20004286
#define FCY (FOSC/2)







#include "ADC.h"
#include "GPS.h"
#include "I2C.h"
#include "Init_Clk.h"
#include "SPI.h"
#include "Timer_ms.h"
#include "UART_PC.h"


#define SEUIL_URGENCE_5V  4.3
extern volatile u8 Mode_Urgence;



#define LED1 LATAbits.LATA2
#define LED1_T TRISAbits.TRISA2
#define LED2 LATCbits.LATC5
#define LED2_T TRISCbits.TRISC5

#define BOUTON_T TRISBbits.TRISB7
#define BOUTON   PORTBbits.RB7
// bouton RB7

#define NRST_GPS_T TRISAbits.TRISA3
#define NRST_GPS    LATAbits.LATA3
#define ON_OFF_GPS_T TRISAbits.TRISA8
#define ON_OFF_GPS    LATAbits.LATA8
// RST  GPS = RA3
// ON OFF GPS = RA8
// RX du GPS = RC4  = RP20
// TX du GPS = RC3  = RP19




#define CSN_RF_T TRISBbits.TRISB3
#define CSN_RF    LATBbits.LATB3
#define RST_RF_T TRISCbits.TRISC6
#define RST_RF    LATCbits.LATC6

// CSN RF RB3
// SPI MISO RB2
// SPI MOSI RB1
// SPI SCLK RB0
// RST RF RC6


#endif	

