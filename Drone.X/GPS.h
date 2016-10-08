
#ifndef __GPS_H
#define __GPS_H


//#define BAUDRATEGPS 1000000
//#define BAUDRATEGPS 500000
//#define BAUDRATEGPS 400000
//#define BAUDRATEGPS 250000
//#define BAUDRATEGPS 200000
//#define BAUDRATEGPS 115200
//#define BAUDRATEGPS 57600
//#define BAUDRATEGPS 38400
//#define BAUDRATEGPS 19200
//#define BAUDRATEGPS 9600
//#define BAUDRATEGPS 4800

#define BAUDRATEGPS 19200

#define BRGBAUDRATEGPS (((FCY / BAUDRATEGPS) / 16) - 1)

#define BRGBAUDRATE_BASE_GPS (((FCY / 4800) / 16) - 1)

#define UART_GPS_SIZE_BUFF 200

// RX du GPS = RC4  = RP20
// TX du GPS = RC3  = RP19

void UART_GPS_Init(void);

u8 Get_Uart_GPS(char *c);

void GPS_Transmit_String(char *str);
void GPS_Transmit_NMEA_Command(u8 *str);
void GPS_Transmit_Char(char symbol);
//

u8 Is_GPS_TX_Empty(void);

void GPS_Send_Off(void);
void GPS_do_Off(void);
void GPS_Send_On_Pin(void);
void Get_Last_GPS_Messages(void);
//void GPS_Querry_Message(void);
void GPS_Go_Fast(void);
void GPS_Go_Slow(void);
void GPS_try_baudrates (void);
void PIC_Go_Slow();
#endif
