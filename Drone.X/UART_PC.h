
#ifndef __UART_PC_H
#define __UART_PC_H


//#define BAUDRATEPC 1000000
//#define BAUDRATEPC 500000
//#define BAUDRATEPC 400000
//#define BAUDRATEPC 250000
//#define BAUDRATEPC 200000
#define BAUDRATEPC 115200
//#define BAUDRATEPC 57600
//#define BAUDRATEPC 38400
//#define BAUDRATEPC 19200
//#define BAUDRATEPC 9600

#define BRGBAUDRATEPC ((FCY / BAUDRATEPC / 16) - 1)

#define UART_SIZE_BUFF 100

void UART_PC_Init(void);
void Transmit_String(char *str);
int	puts(const char *symbol);
void Transmit_Char(char symbol);
u8 Get_Uart(char *c);




#endif
