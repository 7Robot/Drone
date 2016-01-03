
#ifndef __MAIN_H
#define	__MAIN_H

#include <xc.h>

#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>

typedef uint32_t u32;
typedef uint16_t u16;
typedef uint8_t u8;

#define FOSC 80017143    // Freq de l'horloge après la PLL
#define FCY (FOSC/2)


#include "ADC.h"
#include "I2C.h"
#include "Init_Clk.h"
#include "Timer_ms.h"
#include "UART_PC.h"


extern volatile u8 Mode_Urgence;



#define LED1 LATAbits.LATA2
#define LED1_T TRISAbits.TRISA2
#define LED2 LATCbits.LATC5
#define LED2_T TRISCbits.TRISC5





#endif	

