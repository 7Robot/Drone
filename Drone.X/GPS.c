

#include "main.h"
//#include <libpic30.h>
#include <uart.h>

volatile u8 TX_GPS_Buff[UART_GPS_SIZE_BUFF];
volatile u16 i_TX_GPS_Buff = 0, i_TX_GPS_Transmit = 0;
volatile u8 RX_GPS_Buff[UART_GPS_SIZE_BUFF];
volatile u16 i_RX_GPS_Buff = 0;


void UART_GPS_Init(void)
{
    
    char loc_str[30];
    OpenUART2(UART_EN & UART_IDLE_CON & UART_IrDA_DISABLE & UART_MODE_FLOW
        & UART_UEN_00 & UART_DIS_WAKE & UART_DIS_LOOPBACK
        & UART_DIS_ABAUD & UART_UXRX_IDLE_ONE & UART_BRGH_SIXTEEN
        & UART_NO_PAR_8BIT & UART_1STOPBIT,
          UART_INT_TX_BUF_EMPTY & UART_IrDA_POL_INV_ZERO
        & UART_SYNC_BREAK_DISABLED & UART_TX_ENABLE & UART_TX_BUF_NOT_FUL & UART_INT_RX_CHAR
        & UART_ADR_DETECT_DIS & UART_RX_OVERRUN_CLEAR,
          BRGBAUDRATEGPS_BASE);

    /*
    ConfigIntUART2(UART_RX_INT_PR6 & UART_RX_INT_EN
                 & UART_TX_INT_PR6 & UART_TX_INT_DIS);
    */
    IPC7bits.U2RXIP = 6;
    IPC7bits.U2TXIP = 6;
    IEC1bits.U2RXIE = 1;
    
    IFS1bits.U2TXIF = 1;    // init le flag 
    
    // RX du GPS = RC4  = RP20      => a brancher sur TX2
    // TX du GPS = RC3  = RP19      => a brancher sur RX2
        //Remapage uart 2
    
    
    TRISCbits.TRISC3 = 1;
    _U2RXR = 19;
    
    
    _RP20R = 0b0101;  // RP20 = U2TX (p.167)
    
    
    Delay_ms(10);
    sprintf(&loc_str[0],"PSRF100,1,%d,8,1,0", BAUDRATEGPS );
    GPS_Transmit_NMEA_Command(&loc_str[0]);
    while (!Is_GPS_TX_Empty());
    Delay_ms(10);
    U2BRG = BAUDRATEGPS;
            
    
    
    /*
    TRISCbits.TRISC4 = 1;
    _U2RXR = 20;
    TRISCbits.TRISC3 = 1;
    */
}


void __attribute__((interrupt, auto_psv)) _U2TXInterrupt(void) {

    IFS1bits.U2TXIF = 0;
    U2TXREG = TX_GPS_Buff[i_TX_GPS_Transmit];
    //printf("%c", TX_GPS_Buff[i_TX_GPS_Transmit]);
    i_TX_GPS_Transmit++;
    if (i_TX_GPS_Transmit == UART_GPS_SIZE_BUFF)
        i_TX_GPS_Transmit = 0;

    if (i_TX_GPS_Transmit == i_TX_GPS_Buff) // si on a tout transmit, on s'arrete
        IEC1bits.U2TXIE = 0;

}

void __attribute__((interrupt, auto_psv)) _U2RXInterrupt(void) {
    RX_GPS_Buff[i_RX_GPS_Buff] = U2RXREG;
    printf("%c", RX_GPS_Buff[i_RX_GPS_Buff]);
    i_RX_GPS_Buff++;
    if (i_RX_GPS_Buff == UART_GPS_SIZE_BUFF)
        i_RX_GPS_Buff = 0;
    IFS1bits.U2RXIF = 0;
}

u8 Is_GPS_TX_Empty(void)
{
    if (i_TX_GPS_Transmit == i_TX_GPS_Buff)
        return 1;
    else
        return 0;
}


void GPS_Transmit_String(char *str)
{
    while (*str != 0) // while we're not reached the end of the string
    {
        GPS_Transmit_Char(*str);
        //if (*str == '\n')
          //  Transmit_Char('\r');
        str++; // going to next character 
    }
}

void GPS_Transmit_NMEA_Command(u8 *str)
{
    u8 i = 0;
    u8 CheckSum = 0;
    u8 loc_String [10];
    
    GPS_Transmit_Char('$');
    while (str[i]) {
        GPS_Transmit_Char(str[i]);
        CheckSum = CheckSum ^ str[i];
        i ++;
    }
    GPS_Transmit_Char('*');
    sprintf(&loc_String[0], "%02X", CheckSum);
    GPS_Transmit_Char(loc_String[0]);
    GPS_Transmit_Char(loc_String[1]);
    GPS_Transmit_Char('\r');
    GPS_Transmit_Char('\n');
}

void GPS_Transmit_Char(char symbol) {

    u8 i = i_TX_GPS_Buff;
    TX_GPS_Buff[i] = symbol;
    i++;
    if (i == UART_GPS_SIZE_BUFF) {
        i = 0;
    }
    i_TX_GPS_Buff = i;
    IEC1bits.U2TXIE = 1;
}
/*
void test_transmit(void)
{
    u8 i = i_TX_GPS_Buff;
    printf ("%d\n", i);
}

//uint8_t Get_Uart(char *c) {
//    static uint16_t i_RX = 0;
//
//    if (i_RX != i_RX_GPS_Buff) { // si il y a qq chose dans le buffer
//        *c = RX_GPS_Buff[i_RX];
//        i_RX++;
//        if (i_RX == UART_GPS_SIZE_BUFF)
//            i_RX = 0;
//        return 1;
//    } else {
//        return 0;
//    }
//}

*/
u8 Get_Uart_GPS(char *c) {
    static u16 i_RX = 0;

    if (i_RX != i_RX_GPS_Buff) { // si il y a qq chose dans le buffer
        *c = RX_GPS_Buff[i_RX];
        i_RX++;
        if (i_RX == UART_GPS_SIZE_BUFF)
            i_RX = 0;
        return 1;
    } else {
        return 0;
    }
}

void GPS_Send_Off(void)
{
    u8 Count = 0;
    GPS_Transmit_NMEA_Command("PSRF117,16");
    while ((Count < 250) && (!Is_GPS_TX_Empty())) {
        Count++;
        Delay_ms(1);
    }
    if (Is_GPS_TX_Empty())
        printf("OFF Sent! in %d ms\n", Count);
    else
        printf("Failed GPS RST?\n");

    Delay_ms(1000);
    NRST_GPS = 0;
    printf("GPS Rst !\r\n");
}

void GPS_do_Off(void)
{
    printf("High ON_OFF for 300 ms\r\n");
    ON_OFF_GPS = 1;
    Delay_ms(300);
    ON_OFF_GPS = 0;
    
    Delay_ms(2000);
    NRST_GPS = 0;
    printf("GPS Rst !\r\n");
}

void GPS_Send_On_Pin(void)
{
    printf("Enable GPS\r\n");
    NRST_GPS = 1;
    Delay_ms(200);
    
    printf("High ON_OFF for 300 ms\r\n");
    ON_OFF_GPS = 1;
    Delay_ms(300);
    ON_OFF_GPS = 0;
    printf("GPS is running !\r\n");
    
}

void Get_Last_GPS_Messages(void)
{
    char c;
    if (Get_Uart_GPS(&c)) {
        do {
            printf("%c", c);
        }while (Get_Uart_GPS(&c));
    } else {
        printf ("Nothing in buffer\r\n");
    }
}

void GPS_Querry_Message(void)
{
    GPS_Transmit_NMEA_Command("PSRF107,00,01,00,01");
    while (!Is_GPS_TX_Empty());
    printf("sent !\r\n");
}

void GPS_Go_Fast(void)
{
    char loc_str[30];
    U2BRG = (((FCY / 4800) / 16) - 1);  // mise au baudrate par defaut du GPS
    sprintf(&loc_str[0],"PSRF100,1,%d,8,1,0", BAUDRATEGPS );
    GPS_Transmit_NMEA_Command(&loc_str[0]);
    while(!Is_GPS_TX_Empty());
    GPS_Transmit_NMEA_Command(&loc_str[0]);
    while(!Is_GPS_TX_Empty());
    Delay_ms(200);
    U2BRG = BRGBAUDRATEGPS;
}

void GPS_Go_Slow(void)
{
    GPS_Transmit_NMEA_Command("PSRF100,1,4800,8,1,0");
    while(!Is_GPS_TX_Empty());
    Delay_ms(200);
    U2BRG = (((FCY / 4800) / 16) - 1);  // mise au baudrate par defaut du GPS
}

void GPS_try_baudrates (void)
{
    u32 loc_baud;
    char loc_str[30];
    loc_baud = 3000;
    sprintf(&loc_str[0],"PSRF100,1,%d,8,1,0", BAUDRATEGPS );
    
    while (loc_baud < 130000) {
        printf("\rtry %ld bauds", loc_baud);
        U2BRG = (((FCY / loc_baud) / 16) - 1);
        Delay_ms(2);
        // double envoit pour être sûr que le \r\n a bien marché
        GPS_Transmit_String("\r\n\r\n");
        GPS_Transmit_NMEA_Command(&loc_str[0]);
        //GPS_Transmit_NMEA_Command("PSRF100,1,4800,8,1,0");
        while(!Is_GPS_TX_Empty());
       // GPS_Transmit_NMEA_Command(&loc_str[0]);
        //GPS_Transmit_NMEA_Command("PSRF100,1,4800,8,1,0");
        //while(!Is_GPS_TX_Empty());
        Delay_ms(5);
        // locbaud + 2%
        loc_baud = (loc_baud * 101) / 100;
    }
    U2BRG = BRGBAUDRATEGPS;
    
    printf ("\r                                 \r\n\n Done try baudrate\n");
    
}

