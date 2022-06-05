


#include "main.h"

u8 RF_TX_Buff[RF_COMM_SIZE];
u16 RF_TX_Buff_TODO = 0, RF_TX_Buff_DONE = 0;

u8 RF_RX_Buff[RF_COMM_SIZE];
u16 RF_RX_Buff_TODO = 0, RF_RX_Buff_DONE = 0;

u8 RF_Comm_State = RF_COMM_REPOS;

u8 RF_Mode = RF_IS_SLAVE;

u8 RF_Set_Slave_Cmd (void)
{
    RF_Comm_State = RF_COMM_REPOS;
    RF_Mode = RF_IS_SLAVE;
    return 0;
}

u8 RF_Set_Master_Cmd (void)
{
    RF_Comm_State = RF_COMM_REPOS;
    RF_Mode = RF_IS_MASTER;
    return 0;
}


u8 RF_Read_All_Reg_Cmd(void)
{
    u16 i = 0;
    
    Delay_ms(100);
    
    for (i = 0; i < 0x2F; i++) {
        printf ("read 0x%02X : reg 0x%02X\n", i, RF_Read_Reg(i));
        Wait_Transmited();
    }
    for ( i = 0x2F00; i <= 0x2F39; i++)
    {
        printf ("Extended Read 0x%02X : reg 0x%02X\n", (i&0xFF), RF_Read_Reg(i));
        Wait_Transmited();
    }
    printf("\n");
    for ( i = 0x2F64; i <= 0x2FA0; i++)
    {
        printf ("Extended Read 0x%02X : reg 0x%02X\n", (i&0xFF), RF_Read_Reg(i));
        Wait_Transmited();
    }
    printf("\n");
    for ( i = 0x2FD2; i <= 0x2FD9; i++)
    {
        printf ("Extended Read 0x%02X : reg 0x%02X\n", (i&0xFF), RF_Read_Reg(i));
        Wait_Transmited();
    }
    return 0;
}


u8 RF_Send_Packet_Cmd(void)
{
    u16 Count;
    static u8 Count_Packet = 0;
    u8 Buff_TX[10] = {9,0,0,0x40,0x55,0x51,0x52,0x53};
    u8 i, val8, prev_val8;
    Buff_TX[2] = Count_Packet++;
    
    
    val8 = RF_Get_Status();
    printf ("Stat2 0x%02X\n", val8);
    val8 = RF_Read_Reg(CC1120_MARCSTATE);
    printf ("MARC 0x%02X\n", val8);
    // ecrit le buffer dans la fifo
    for (i = 0; i < 10; i++) {
        RF_Write_Reg(CC1120_SINGLE_TXFIFO, Buff_TX[i]);
        printf("0x%02X,", Buff_TX[i] );
    }
    printf("\n");
    RF_Send_Command(CC1120_STX);
    
    // PKT_Config  modifié
    //RF_Write_Reg(CC1120_PKT_CFG0, (RF_Read_Reg(CC1120_PKT_CFG0) & 0x9F));
    //RF_Write_Reg(CC1120_PKT_LEN,5);
    /*
    RF_Write_Reg(CC1120_SYNC3,0x26);
    RF_Write_Reg(CC1120_SYNC2,0x33);
    RF_Write_Reg(CC1120_SYNC1,0xd9);
    RF_Write_Reg(CC1120_SYNC0,0xcc);
    
          // Strobe TX to send packet 1
      //-----------------------------------------------------------------------------
      // 0xAA 0xAA 0xAA |  0x26 0x33 0xD9 0xCC | 0x55 0x20 0x30 0x40 0x55 | CRC CRC |
      //-----------------------------------------------------------------------------
    
    Delay_ms (1);
    val8 = RF_Read_Reg(CC1120_NUM_TXBYTES);
    printf ("il y a %d bytes dans la fifo TX\n", val8);
    Wait_Transmited();
    // lance la transmission
    printf ("Stat0 0x%02X\n", RF_Get_Status());
    RF_Send_Command(CC1120_STX);
    printf("Buffer sent\n");
    printf ("Stat1 0x%02X\n", RF_Get_Status());
    Wait_Transmited();
    */
    val8 = RF_Read_Reg(CC1120_NUM_TXBYTES);
    prev_val8 = val8;
    Count = 0;
    while (val8 && (Count < 5000)) {
        Delay_ms(1);
        val8 = RF_Read_Reg(CC1120_NUM_TXBYTES);
        if (val8 != prev_val8) {
            prev_val8 = val8;
            printf("%d bytes in fifo TX after %d ms\n", val8, Count);
        }
        Count ++;
    }
    val8 = RF_Get_Status();
    printf ("Stat2 0x%02X\n", val8);
    val8 = RF_Read_Reg(CC1120_MARCSTATE);
    printf ("MARC 0x%02X\n", val8);
    Delay_ms(50);
    val8 = RF_Get_Status();
    printf ("Stat2 0x%02X\n", val8);
    val8 = RF_Read_Reg(CC1120_MARCSTATE);
    printf ("MARC 0x%02X\n", val8);
    Delay_ms(50);
    val8 = RF_Get_Status();
    printf ("Stat2 0x%02X\n", val8);
    val8 = RF_Read_Reg(CC1120_MARCSTATE);
    printf ("MARC 0x%02X\n", val8);
    Delay_ms(50);
    
    return 0;
}


u8 RF_Wait_For_Packet_Cmd(void)
{
    u8 val8, c;
    u8 Marc8;
    u8 i, buff;
    //u8 last_receive = 1;
    u8 receive = 0;
    u16 val16 = 0;
//    
//    // PKT_Config  modifié
//    RF_Write_Reg(CC1120_PKT_CFG0, (RF_Read_Reg(CC1120_PKT_CFG0) & 0x9F));
//    
//    RF_Write_Reg(CC1120_PKT_LEN,5);
//    
//    RF_Write_Reg(CC1120_SYNC3,0x26);
//    RF_Write_Reg(CC1120_SYNC2,0x33);
//    RF_Write_Reg(CC1120_SYNC1,0xd9);
//    RF_Write_Reg(CC1120_SYNC0,0xcc);
//    
//    // Set RX Filter BW (12.5 kHz)
//    //RF_Write_Reg(CC1120_CHAN_BW,0x10);
//    RF_Write_Reg(CC1120_CHAN_BW,0x05);
//    
//  // Clear FREQOFF register in case prev. compensation has been done on a
//  // faulty packet
//    RF_Write_Reg(CC1120_FREQOFF1,0);
//    RF_Write_Reg(CC1120_FREQOFF0,0);
    
    printf("Start Receive Mode\n");
    Wait_Transmited();
    // passe en mode reception
    RF_Send_Command(CC1120_SRX);
    i = 0;
    while ((RF_Read_Reg(CC1120_MARCSTATE) != 0x6D) && (i < 200)) {
        i ++;
        Delay_ms(1);
    }
    if (i == 200)
        printf ("error set RX\n");
    
    val8 = RF_Get_Status();
    printf ("Stat2 0x%02X\n", val8);
    
    Marc8 = RF_Read_Reg(CC1120_MARCSTATE);
    // on reste dans ce mode tant que l'utilisateur n'a pas appuyé sur une touche
    while (!Get_Uart(&c)) {
        //receive = RF_Read_Reg(CC1120_SINGLE_RXFIFO);
        /*
        if (RF_Get_Status() != 0x10) {      // si on n'est plus en mode RX
            receive = RF_Read_Reg(CC1120_NUM_RXBYTES);
            printf("%d receive\r\n", receive);
            receive = 10;
            while (receive) {
                buff = RF_Read_Reg(CC1120_SINGLE_RXFIFO);
                printf("%5d 0x%02X\r\n", val16, buff);
                receive--; // = RF_Read_Reg(CC1120_NUM_RXBYTES);
            }
            RF_Set_RX_Mode();
            printf("Reset RX\r\n");
        }*/
        
        receive = RF_Read_Reg(CC1120_NUM_RXBYTES);
        if (receive) {
            buff = RF_Read_Reg(CC1120_RXFIRST);
            printf("%5d 0x%02X\r\n", val16, buff);
            
            val8 = RF_Get_Status();
            if (!val8) {
                RF_Set_RX_Mode();
                printf("Reset RX\r\n");
            }
        }
        val8 = RF_Read_Reg(CC1120_MARCSTATE);
        if (val8 != Marc8) {
            printf("%5d MARC : 0x%02X\r\n", val16, val8);
            Marc8 = val8;
        }
        
        //if (receive != last_receive) {
            //printf("0x%02X ", receive);
            //last_receive = receive;
        //}
        /*
        val8 = RF_Read_Reg(CC1120_NUM_RXBYTES);
        if (val8) {
            LED1 = !LED1;
            printf("recu %d octets : ", val8);
            for (i = 0; i < val8; i++) {
                buff = 
                printf("0x%02X ", buff);
            }
            printf ("\n");
        }*/
        Delay_ms(1);
        val16 ++;
    }
    
    printf("Leaving Receive Mode\n");
    return 0;
}


