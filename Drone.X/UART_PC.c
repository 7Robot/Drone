

#include "main.h"
//#include <libpic30.h>
#include <uart.h>

volatile u8 TX_PC_Buff[UART_PC_SIZE_BUFF];
volatile u16 i_TX_PC_Buff = 0;
volatile u8 RX_PC_Buff[UART_PC_SIZE_BUFF];
volatile u16 i_RX_PC_Buff = 0;


void UART_PC_Init(void)
{
    
    OpenUART1(UART_EN & UART_IDLE_CON & UART_IrDA_DISABLE & UART_MODE_FLOW
        & UART_UEN_00 & UART_DIS_WAKE & UART_DIS_LOOPBACK
        & UART_DIS_ABAUD & UART_UXRX_IDLE_ONE & UART_BRGH_SIXTEEN
        & UART_NO_PAR_8BIT & UART_1STOPBIT,
          UART_INT_TX_BUF_EMPTY & UART_IrDA_POL_INV_ZERO
        & UART_SYNC_BREAK_DISABLED & UART_TX_ENABLE & UART_TX_BUF_NOT_FUL & UART_INT_RX_CHAR
        & UART_ADR_DETECT_DIS & UART_RX_OVERRUN_CLEAR,
          BRGBAUDRATEPC);


    ConfigIntUART1(UART_RX_INT_PR7 & UART_RX_INT_EN
                 & UART_TX_INT_PR7 & UART_TX_INT_DIS);
    
    IFS0bits.U1TXIF = 1;    // init le flag 
    
    //Remapage uart 1
    _U1RXR = 24;
    _RP23R = 0b0011;  // RP23 = U1TX (p.167)
}


void __attribute__((interrupt, auto_psv)) _U1TXInterrupt(void) {
    static u16 i_TX_Transmit = 0;

    IFS0bits.U1TXIF = 0;
    U1TXREG = TX_PC_Buff[i_TX_Transmit];
    i_TX_Transmit++;
    if (i_TX_Transmit == UART_PC_SIZE_BUFF)
        i_TX_Transmit = 0;

    if (i_TX_Transmit == i_TX_PC_Buff) // si on a tout transmit, on s'arrete
        IEC0bits.U1TXIE = 0;
}

void __attribute__((interrupt, auto_psv)) _U1RXInterrupt(void) {
    u16 i = i_RX_PC_Buff;
    RX_PC_Buff[i] = U1RXREG;
    i++;
    if (i == UART_PC_SIZE_BUFF)
        i = 0;
    i_RX_PC_Buff = i;
    IFS0bits.U1RXIF = 0;
}

u8 Is_TX_Empty(void)
{
    return !IEC0bits.U1TXIE;
}

int write(int handle, void *buffer, unsigned int len)
{
    unsigned int i;
    char *buff = buffer;
 //   if (handle == 0) {
        for (i = 0; i < len; i ++) {
            Transmit_Char(*buff);
            buff ++;
        }
 //   }
    //Transmit_Char('c');
    return len;
}

void Transmit_Char(char symbol) {

    u8 i = i_TX_PC_Buff;
    TX_PC_Buff[i] = symbol;
    i++;
    if (i == UART_PC_SIZE_BUFF) {
        i = 0;
    }
    i_TX_PC_Buff = i;
    IEC0bits.U1TXIE = 1;
}

//void test_transmit(void)
//{
//    u8 i = i_TX_PC_Buff;
//    printf ("%d\n", i);
//}

u8 Get_Uart(char *c) {
    static u16 i_RX = 0;

    if (i_RX != i_RX_PC_Buff) { // si il y a qq chose dans le buffer
        *c = RX_PC_Buff[i_RX];
        i_RX++;
        if (i_RX == UART_PC_SIZE_BUFF)
            i_RX = 0;
        return 1;
    } else {
        return 0;
    }
}



