

#include "main.h"

volatile u8 TX_PC_Buff[UART_PC_SIZE_BUFF];
volatile u16 i_TX_PC_Buff = 0;
volatile u8 RX_PC_Buff[UART_PC_SIZE_BUFF];
volatile u16 i_RX_PC_Buff = 0;


void UART_PC_Init(void)
{
    u8 poubelle;
    
    IFS0bits.U1RXIF = 0;
    IFS0bits.U1TXIF = 0;
    
    i_TX_PC_Buff = 0;
    i_RX_PC_Buff = 0;
    
    U1STAbits.UTXISEL1 = 1;
    U1STAbits.UTXISEL0 = 0;     // une interruption quand le buffer est vide
    U1STAbits.URXISEL = 0;      // IT en RX des la 1ere reception
    
    U1MODEbits.UARTEN = 1;      // va par defaut du registre OK (mode 8bit)
    U1STAbits.UTXEN = 1;        // enable TX  (apres UARTEN, sinon marche pas)
    U1BRG = BRGBAUDRATEPC;

    //Remapage uart 1
    _U1RXR = 24;
    _RP23R = 0b0011;  // RP23 = U1TX (p.167)
    
    // purge buffer r�cepetion
    IFS0bits.U1RXIF = 0;
    poubelle = U1RXREG;
    poubelle = U1RXREG;
    poubelle = U1RXREG;
    poubelle = U1RXREG;

    // vu qu'on peut gerer 4 transmits � la fois, c'est plus une IT super urgente..

    IPC2bits.U1RXIP = 4;
    IPC3bits.U1TXIP = 4;
    IEC0bits.U1RXIE = 1;
    IEC0bits.U1TXIE = 0;
    
    IFS0bits.U1TXIF = 1; // init le flag 

}

    
    
void __attribute__((interrupt, auto_psv)) _U1TXInterrupt(void)
{
    static u16 i_TX_Transmit = 0;
    // cette IT d�clenche quand le buffer (FIFO de 4 places) devient vide
    // par contre, le shift register (ce qui est en train de transm�tre), n'est pas forc�ment vide
    // on rajoute des choses dans la FIFO tant qu'elle n'est pas pleine, et tant que l'on a qqchose � envoyer
    
    while ((i_TX_Transmit != i_TX_PC_Buff) && (!U1STAbits.UTXBF)) {
        IFS0bits.U1TXIF = 0;
        U1TXREG = TX_PC_Buff[i_TX_Transmit];
        i_TX_Transmit++;
        if (i_TX_Transmit >= UART_PC_SIZE_BUFF)
            i_TX_Transmit = 0;
    }
    
    if (i_TX_Transmit == i_TX_PC_Buff) // si on a tout transmit, on s'arrete
        IEC0bits.U1TXIE = 0;
}

void __attribute__((interrupt, auto_psv)) _U1RXInterrupt(void)
{
    u16 i = i_RX_PC_Buff;
    while (U1STAbits.URXDA) {      // tant que la FIFO de r�ception n'est pas vide
        IFS0bits.U1RXIF = 0;
        RX_PC_Buff[i] = U1RXREG;
        i++;
        if (i >= UART_PC_SIZE_BUFF)
            i = 0;
    }
    i_RX_PC_Buff = i;
}

u8 Is_TX_Empty(void)
{
    return !IEC0bits.U1TXIE;
}

void Wait_Transmited(void)
{   while(!Is_TX_Empty());  }

int write(int handle, void *buffer, unsigned int len)
{
    unsigned int i;
    u8 *buff = buffer;
 //   if (handle == 0) {
        for (i = 0; i < len; i ++) {
            Transmit_Char(*buff);
            buff ++;
        }
 //   }
    //Transmit_Char('c');
    return len;
}

void Transmit_Char(u8 symbol) {

    u16 i = i_TX_PC_Buff;
    TX_PC_Buff[i] = symbol;
    i++;
    if (i >= UART_PC_SIZE_BUFF) {
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

u8 Get_Uart(u8 *c) {
    static u16 i_RX = 0;

    if (i_RX != i_RX_PC_Buff) { // si il y a qq chose dans le buffer
        *c = RX_PC_Buff[i_RX];
        i_RX++;
        if (i_RX >= UART_PC_SIZE_BUFF)
            i_RX = 0;
        return 1;
    } else {
        return 0;
    }
}



