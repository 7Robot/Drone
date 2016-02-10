


#include "main.h"


u8 RF_Reset_Actif = 1;

 
// Address config = No address check 
// Packet bit length = 0 
// Whitening = false 
// Carrier frequency = 868.000000 
// Manchester enable = false 
// Bit rate = 0.6 
// Deviation = 1.499176 
// Symbol rate = 0.6 
// Performance mode = High Performance 
// RX filter BW = 12.500000 
// Device address = 0 
// Modulation format = 2-GFSK 
// PA ramping = true 
// Packet length = 255 
// TX power = 15 
// Packet length mode = Variable 
#define NUMBER_OF_CONFIG_REGISTER 44
static const u16 preferredSettings868[NUMBER_OF_CONFIG_REGISTER][2]= 
{
  {CC1120_IOCFG3,            0xB0},
  {CC1120_IOCFG2,            0x06},
  {CC1120_IOCFG1,            0xB0},
  {CC1120_IOCFG0,            0x40},
  {CC1120_SYNC3,             0x26},
  {CC1120_SYNC2,             0x33},
  {CC1120_SYNC1,             0xD9},
  {CC1120_SYNC0,             0xCC},
  {CC1120_SYNC_CFG1,         0x08},
  {CC1120_DEVIATION_M,       0x89},
  {CC1120_MODCFG_DEV_E,      0x09},
  {CC1120_DCFILT_CFG,        0x1C},
  {CC1120_IQIC,              0xC6},
  {CC1120_CHAN_BW,           0x10},
  {CC1120_SYMBOL_RATE2,      0x33},
  {CC1120_AGC_REF,           0x20},
  {CC1120_AGC_CS_THR,        0x19},
  {CC1120_AGC_CFG1,          0xA9},
  {CC1120_AGC_CFG0,          0xCF},
  {CC1120_FIFO_CFG,          0x00},
  {CC1120_SETTLING_CFG,      0x03},
  {CC1120_FS_CFG,            0x12},
  {CC1120_PKT_CFG0,          0x20},
  {CC1120_PA_CFG0,           0x7E},
  {CC1120_PKT_LEN,           0xFF},
  {CC1120_IF_MIX_CFG,        0x00},
  {CC1120_FREQOFF_CFG,       0x30},
  {CC1120_FREQ2,             0x6C},
  {CC1120_FREQ1,             0x80},
  {CC1120_FS_DIG1,           0x00},
  {CC1120_FS_DIG0,           0x5F},
  {CC1120_FS_CAL1,           0x40},
  {CC1120_FS_CAL0,           0x0E},
  {CC1120_FS_DIVTWO,         0x03},
  {CC1120_FS_DSM0,           0x33},
  {CC1120_FS_DVC0,           0x17},
  {CC1120_FS_PFD,            0x50},
  {CC1120_FS_PRE,            0x6E},
  {CC1120_FS_REG_DIV_CML,    0x14},
  {CC1120_FS_SPARE,          0xAC},
  {CC1120_FS_VCO0,           0xB4},
  {CC1120_LNA,               0x03},
  {CC1120_XOSC5,             0x0E},
  {CC1120_XOSC1,             0x03},
};
/*
// Carrier frequency = 868.000000 
// Symbol rate = 1.2 
// Bit rate = 1.2 
// Deviation = 3.997803 
// Manchester enable = false 
// Bit rate = 1.2 
// Modulation format = 2-FSK 
// Bit rate = 1.2 
// RX filter BW = 25.000000 
// TX power = -6 
// PA ramping = true 
// Packet length mode = Variable 
// Whitening = false 
// Address config = No address check. 
// Packet length = 255 
// Device address = 0 
        
#define NUMBER_OF_CONFIG_REGISTER 40
static const u16 preferredSettings868[NUMBER_OF_CONFIG_REGISTER][2]= 
{
    {CC1120_IOCFG3,         0xB0},
    {CC1120_IOCFG2,         0x06},
    {CC1120_IOCFG1,         0xB0},
    {CC1120_IOCFG0,         0xB0},
    {CC1120_SYNC_CFG1,      0x0B},
    {CC1120_DCFILT_CFG,     0x1C},
    {CC1120_IQIC,           0xC6},
    {CC1120_CHAN_BW,        0x08},
    {CC1120_MDMCFG0,        0x05},
    {CC1120_AGC_REF,        0x20},
    {CC1120_AGC_CS_THR,     0x19},
    {CC1120_AGC_CFG1,       0xA9},
    {CC1120_AGC_CFG0,       0xCF},
    {CC1120_FIFO_CFG,       0x00},
    {CC1120_SETTLING_CFG,   0x03},
    {CC1120_FS_CFG,         0x12},
    {CC1120_PKT_CFG1,       0x05},  
    {CC1120_PKT_CFG0,       0x20},
    {CC1120_PA_CFG2,        0x4F},
    {CC1120_PA_CFG1,        0x56},
    {CC1120_PA_CFG0,        0x1C},
    {CC1120_PKT_LEN,        0xFF},
    {CC1120_IF_MIX_CFG,     0x00},
    {CC1120_FREQOFF_CFG,    0x22},
    {CC1120_FREQ2,          0x6C},
    {CC1120_FREQ1,          0x80},
    {CC1120_FREQ0,          0x00},
    {CC1120_FS_DIG1,        0x00},
    {CC1120_FS_DIG0,        0x5F},
    {CC1120_FS_CAL0,        0x0E},
    {CC1120_FS_DIVTWO,      0x03},
    {CC1120_FS_DSM0,        0x33},
    {CC1120_FS_DVC0,        0x17},
    {CC1120_FS_PFD,         0x50},
    {CC1120_FS_PRE,         0x6E},
    {CC1120_FS_REG_DIV_CML, 0x14},
    {CC1120_FS_SPARE,       0xAC},
    {CC1120_XOSC5,          0x0E},
    {CC1120_XOSC3,          0xC7},
    {CC1120_XOSC1,          0x07}
};

*/

void SPI_Init(void)
{
    u16 titi;
// SPI MISO RB2     = RP2       // in
// SPI MOSI RB1     = RP1       // out
// SPI SCLK RB0     = RP0       // out
    
   _RP0R = 0b01000;     // SPI1 clk
   _SCK1R = 0;
   _RP1R = 0b00111;     // SPI data out
   _SDI1R = 2;
   
   
   
   SPI1CON1bits.MODE16 = 0; // mode 8 bits
   SPI1CON1bits.SMP = 0;    // latch de la data in au milieu de la présence de data out
   SPI1CON1bits.CKP = 0;    // clk repos = 0, clk active = 1
   SPI1CON1bits.CKE = 1;    // change la data quand la clock passe de active à repos (de 1 à 0)
   SPI1CON1bits.MSTEN = 1;  //  mode master 
   
   SPI1CON1bits.PPRE = 0;   // prim precale à 1/64
   SPI1CON1bits.SPRE = 0;   // second prescale à 1/8
   // =>  1/512 depuis la clock principale (40MHz))     => 78 kHz
   
   SPI1STATbits.SPIEN = 1;  // active le SPI !
   
   titi = SPI1BUF;
      
}



void RF_Reset(void)
{
    if (RF_Reset_Actif) {
        printf ("Active RF\n");
    } else {
        printf ("Desactive RF\n");
    }
    RST_RF = RF_Reset_Actif;
    RF_Reset_Actif = !RF_Reset_Actif;
}

u8 RF_Get_Status(void)
{
    u8 val8;
    CSN_RF = 0;

    SPI1BUF = 0x80; // lecture registre 0...
    
    while (!SPI1STATbits.SPIRBF);
    val8 = SPI1BUF;
    
    CSN_RF = 1;
    
    return val8;
}

u8 RF_Read_Reg(u16 reg_addr)
{
    u8 val8, reg8;
    reg8 = (u8)(reg_addr & 0xFF);
    CSN_RF = 0;
    if (reg_addr & 0xFF00) {
        SPI1BUF = 0x80 | 0x2F;
        while (!SPI1STATbits.SPIRBF);
        val8 = SPI1BUF;
        SPI1BUF = reg8;
    } else {
        SPI1BUF = 0x80 | reg8;
    }
    while (!SPI1STATbits.SPIRBF);
    val8 = SPI1BUF;
    SPI1BUF = 0;    // write vierge pour faire le transfert !
    while (!SPI1STATbits.SPIRBF);
    val8 = SPI1BUF; 
    CSN_RF = 1;
    
    return val8;
}

u8 RF_Send_Command(u8 cmd)
{
    u8 val8;
    CSN_RF = 0;

    SPI1BUF = cmd;
    
    while (!SPI1STATbits.SPIRBF);
    val8 = SPI1BUF;
    
    CSN_RF = 1;
    
    return val8;
}

void RF_Write_Reg(u16 reg_addr, u8 Data)
{
    u8 val8, reg8;
    reg8 = (u8)(reg_addr & 0xFF);
    CSN_RF = 0;
    if (reg_addr & 0xFF00) {
        SPI1BUF = 0x2F;
        while (!SPI1STATbits.SPIRBF);
        val8 = SPI1BUF;
        SPI1BUF = reg8;
    } else {
        SPI1BUF = reg8;
    }
    while (!SPI1STATbits.SPIRBF);
    val8 = SPI1BUF;
    SPI1BUF = Data;
    Maxtime = 20;
    while (!SPI1STATbits.SPIRBF);
    val8 = SPI1BUF; 
    CSN_RF = 1;
    
}


void RF_Read_All_Reg(void)
{
    u16 i;
    
    RF_Send_Command(CC1120_SRES);
    Delay_ms(100);
    
    for (i = 0; i < 0x2F; i++) {
        printf ("read 0x%02X : reg 0x%02X\n", i, RF_Read_Reg(i));
        while(!Is_TX_Empty());
    }
    for ( i = 0x2F00; i <= 0x2F39; i++)
    {
        printf ("Extended Read 0x%02X : reg 0x%02X\n", (i&0xFF), RF_Read_Reg(i));
        while(!Is_TX_Empty());
    }
    for ( i = 0x2F64; i <= 0x2FA0; i++)
    {
        printf ("Extended Read 0x%02X : reg 0x%02X\n", (i&0xFF), RF_Read_Reg(i));
        while(!Is_TX_Empty());
    }
    for ( i = 0x2FD2; i <= 0x2FD9; i++)
    {
        printf ("Extended Read 0x%02X : reg 0x%02X\n", (i&0xFF), RF_Read_Reg(i));
        while(!Is_TX_Empty());
    }
}

void RF_ON (void)
{
    u16 i;
    if (RF_Reset_Actif) {
        RF_Reset();
    }
    
    Delay_ms(100);
    printf("Reset de la carte RF\n");
    RF_Send_Command(CC1120_SRES);
    Maxtime = 1000;
    while (RF_Get_Status() && Maxtime);
    printf("Reset in %ld ms\n", 1000 - Maxtime);
    printf ("Write all config register\n");
    
    for (i = 0; i < NUMBER_OF_CONFIG_REGISTER; i++) {
        RF_Write_Reg(preferredSettings868[i][0], preferredSettings868[i][1]);
        if (i == (NUMBER_OF_CONFIG_REGISTER-1)) {
            printf ("Last is 0x%04X, 0x%02X\n", preferredSettings868[i][0], preferredSettings868[i][1]);
        }
    }
    printf("Calibration : \n");
    RF_Manual_Calib(1);
    printf ("RF is working\n");
    
}


void RF_Manual_Calib(u8 verbose)
{
    u8 original_fs_cal2;
    u8 high_FS_VCO2, high_FS_VCO4, high_FS_CHP;
    u8 mid_FS_VCO2, mid_FS_VCO4, mid_FS_CHP;
    // SET VCO CAP ARRAY TO 0 :
    RF_Write_Reg(CC1120_FS_VCO2,0);
    // read FS CAL 2 and store it
    original_fs_cal2 = RF_Read_Reg(CC1120_FS_CAL2);
    // Re-write it with original_fs_cal2 + 2
    if (verbose)
        printf("original fs_cal = 0x%02X\n", original_fs_cal2);
    RF_Write_Reg(CC1120_FS_CAL2, original_fs_cal2 + 2);
    Delay_ms (10);
    
    // strobe calibration
    RF_Send_Command(CC1120_SCAL);
    Maxtime = 1000;
    
    // wait for MARC STATE to be IDLE
    while ( (RF_Read_Reg(CC1120_MARCSTATE) != 0x41) && (!Maxtime) ) {
        Delay_ms(1);
    }
    if (!Maxtime)
        printf("Maxtime calib 1 !\n");
    
    // read result
    high_FS_VCO2 = RF_Read_Reg(CC1120_FS_VCO2);
    high_FS_VCO4 = RF_Read_Reg(CC1120_FS_VCO4);
    high_FS_CHP = RF_Read_Reg(CC1120_FS_CHP);
    if (verbose)
        printf("Results high : FS_VCO2 : 0x%02X, FS_VCO4 : 0x%02X, FS_CHP : 0x%02X\n", high_FS_VCO2, high_FS_VCO4, high_FS_CHP);
    
    
    // SET VCO CAP ARRAY TO 0 :
    RF_Write_Reg(CC1120_FS_VCO2,0);
    // Re-write with original_fs_cal2
    RF_Write_Reg(CC1120_FS_CAL2, original_fs_cal2);
    Delay_ms (10);
    
    // strobe calibration
    RF_Send_Command(CC1120_SCAL);
    Maxtime = 1000;
    
    // wait for MARC STATE to be IDLE
    while ( (RF_Read_Reg(CC1120_MARCSTATE) != 0x41) && (!Maxtime) ) {
        Delay_ms(1);
    }
    if (!Maxtime)
        printf("Maxtime calib 2 !\n");
    
    // read result
    mid_FS_VCO2 = RF_Read_Reg(CC1120_FS_VCO2);
    mid_FS_VCO4 = RF_Read_Reg(CC1120_FS_VCO4);
    mid_FS_CHP = RF_Read_Reg(CC1120_FS_CHP);
    if (verbose)
        printf("Results mid : FS_VCO2 : 0x%02X, FS_VCO4 : 0x%02X, FS_CHP : 0x%02X\n", mid_FS_VCO2, mid_FS_VCO4, mid_FS_CHP);
    
    if (high_FS_VCO2 > mid_FS_VCO2) {
        RF_Write_Reg(CC1120_FS_VCO2, high_FS_VCO2);
        RF_Write_Reg(CC1120_FS_VCO4, high_FS_VCO4);
        RF_Write_Reg(CC1120_FS_CHP, high_FS_CHP);
    } else {
        RF_Write_Reg(CC1120_FS_VCO2, mid_FS_VCO2);
        RF_Write_Reg(CC1120_FS_VCO4, mid_FS_VCO4);
        RF_Write_Reg(CC1120_FS_CHP, mid_FS_CHP);
    }
}

void RF_Send_Packet(void)
{
    u16 Count;
    u8 Buff_TX[5] = {0x55,0x20,0x30,0x40,0x55};
    u8 i, val8, prev_val8;
    // ecrit le buffer dans la fifo
    for (i = 0; i < 5; i++) {
        RF_Write_Reg(CC1120_SINGLE_TXFIFO, Buff_TX[i]);
    }

    // PKT_Config  modifié
    RF_Write_Reg(CC1120_PKT_CFG0, (RF_Read_Reg(CC1120_PKT_CFG0) & 0x9F));
    RF_Write_Reg(CC1120_PKT_LEN,5);
    
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
    // lance la transmission
    printf ("Stat0 0x%02X\n", RF_Get_Status());
    RF_Send_Command(CC1120_STX);
    printf("Buffer sent\n");
    printf ("Stat1 0x%02X\n", RF_Get_Status());
    
    //val8 = RF_Read_Reg(CC1120_NUM_TXBYTES);
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
    
}

void RF_Wait_For_Packet(void)
{
    u8 val8, c;
    u8 i, buff;
    
    // PKT_Config  modifié
    RF_Write_Reg(CC1120_PKT_CFG0, (RF_Read_Reg(CC1120_PKT_CFG0) & 0x9F));
    
    RF_Write_Reg(CC1120_PKT_LEN,5);
    
    RF_Write_Reg(CC1120_SYNC3,0x26);
    RF_Write_Reg(CC1120_SYNC2,0x33);
    RF_Write_Reg(CC1120_SYNC1,0xd9);
    RF_Write_Reg(CC1120_SYNC0,0xcc);
    
    // Set RX Filter BW (12.5 kHz)
    //RF_Write_Reg(CC1120_CHAN_BW,0x10);
    RF_Write_Reg(CC1120_CHAN_BW,0x05);
    
  // Clear FREQOFF register in case prev. compensation has been done on a
  // faulty packet
    RF_Write_Reg(CC1120_FREQOFF1,0);
    RF_Write_Reg(CC1120_FREQOFF0,0);
    
    printf("Start Receive Mode\n");
    // passe en mode reception
    RF_Send_Command(CC1120_SRX);
    i = 0;
    while ((RF_Read_Reg(CC1120_MARCSTATE) != 0x6D) && (i < 200)) {
        i ++;
        Delay_ms(1);
    }
    if (i == 200)
        printf ("error set RX\n");
    
    // on reste dans ce mode tant que l'utilisateur n'a pas appuyé sur une touche
    while (!Get_Uart(&c)) {
        val8 = RF_Read_Reg(CC1120_NUM_RXBYTES);
        if (val8) {
            LED1 = !LED1;
            printf("recu %d octets : ", val8);
            for (i = 0; i < val8; i++) {
                buff = RF_Read_Reg(CC1120_SINGLE_RXFIFO);
                printf("0x%02X ", buff);
            }
            printf ("\n");
        }
        Delay_ms(1);
    }
    
    printf("Leaving Receive Mode\n");
}


