


#include "main.h"


u8 RF_Reset_Actif = 1;

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
static const u16 preferredSettings868[][2] = {
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
    {CC1120_XOSC1,          0x07},
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



static const u16 preferredSettings868[][2] = {
  {CC1120_IOCFG0,        0x06},
  {CC1120_SYNC_CFG1,     0x0B},
  {CC1120_DCFILT_CFG,    0x1C},
  {CC1120_IQIC,          0xC6},
  {CC1120_CHAN_BW,       0x08},
  {CC1120_MDMCFG0,       0x05},
  {CC1120_AGC_REF,       0x20},
  {CC1120_AGC_CS_THR,    0x19},
  {CC1120_AGC_CFG1,      0xA9},
  {CC1120_AGC_CFG0,      0xCF},
  {CC1120_FIFO_CFG,      0x00},
  {CC1120_SETTLING_CFG,  0x03},
  {CC1120_FS_CFG,        0x12},
  {CC1120_PKT_CFG1,      0x05},  
  {CC1120_PKT_CFG0,      0x20},
  {CC1120_PA_CFG2,       0x4F},
  {CC1120_PA_CFG1,       0x56},
  {CC1120_PA_CFG0,       0x1C},
  {CC1120_PKT_LEN,       0xFF},
  {CC1120_IF_MIX_CFG,    0x00},
  {CC1120_FREQOFF_CFG,   0x22},
  {CC1120_FREQ2,         0x6C},
  {CC1120_FREQ1,         0xA0}, //869
//  {CC1120_FREQ1,         0x80}, //868
  {CC1120_FREQ0,         0x00},
  {CC1120_FS_DIG1,       0x00},
  {CC1120_FS_DIG0,       0x5F},
  {CC1120_FS_CAL0,       0x0E},
  {CC1120_FS_DIVTWO,     0x03},
  {CC1120_FS_DSM0,       0x33},
  {CC1120_FS_DVC0,       0x17},
  {CC1120_FS_PFD,        0x50},
  {CC1120_FS_PRE,        0x6E},
  {CC1120_FS_REG_DIV_CML,0x14},
  {CC1120_FS_SPARE,      0xAC},
  {CC1120_XOSC5,         0x0E},
  {CC1120_XOSC3,         0xC7},
  {CC1120_XOSC1,         0x07},
};

static const u16 SettingsTemp[][2] = {
  {CC1120_DCFILT_CFG,    0x40},
  {CC1120_MDMCFG1,       0x47},
  {CC1120_CHAN_BW,       0x81},
  {CC1120_FREQ_IF_CFG,   0x00},
  {CC1120_ATEST,         0x2A},
  {CC1120_ATEST_MODE,    0x07},
  {CC1120_GBIAS1,        0x07},
  {CC1120_PA_IFAMP_TEST, 0x01},
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
   
   
   SPI1STATbits.SPIEN = 0;  // desactive le SPI !
   
   
   SPI1CON1bits.MODE16 = 0; // mode 8 bits
   SPI1CON1bits.SMP = 1;    // latch de la data in à la fin de la présence de data out
   //SPI1CON1bits.CKP = 0;    // clk repos = 0, clk active = 1
   //SPI1CON1bits.CKE = 1;    // change la data quand la clock passe de active à repos (de 1 à 0)
   SPI1CON1bits.CKP = 1;
   SPI1CON1bits.CKE = 0;
   SPI1CON1bits.MSTEN = 1;  //  mode master 
   
   SPI1CON1bits.PPRE = 1;   // prim precale à 1/4
   SPI1CON1bits.SPRE = 2;   // second prescale à 1/4
   // =>  1/16 depuis la clock principale (40MHz))     => 2.5MH
   
   SPI1STATbits.SPIEN = 1;  // active le SPI !
   
   titi = SPI1BUF;
      
}



void RF_Reset_Cmd(void)
{
    if (RF_Reset_Actif) {
        SPI_Init();
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
    val8 = SPI1BUF; // clear
    reg8 = (u8)(reg_addr & 0xFF);
    CSN_RF = 0;
    if (reg_addr & 0xFF00) {
        SPI1BUF = 0x80 | (reg_addr >> 8);
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

void RF_Write_Reg(u16 reg_addr, u8 Data)
{
    u8 val8, reg8;
    val8 = SPI1BUF;
    reg8 = (u8)(reg_addr & 0xFF);
    CSN_RF = 0;
    if (reg_addr & 0xFF00) {
        SPI1BUF = (reg_addr >> 8);
        while (!SPI1STATbits.SPIRBF);
        val8 = SPI1BUF;
    }
    SPI1BUF = reg8;
    while (!SPI1STATbits.SPIRBF);
    val8 = SPI1BUF;
    
    SPI1BUF = Data;
    while (!SPI1STATbits.SPIRBF);
    val8 = SPI1BUF; 
    CSN_RF = 1;
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


void RF_Read_All_Reg_Cmd(void)
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
}

void RF_Init_Cmd (void)
{
    u16 i;
    u8 val8;
    
    RF_Reset_Actif = 0;
    RST_RF = 1;
    
    SPI_Init();
    
    Delay_ms(100);
    printf("Reset de la carte RF\n");
    Wait_Transmited();
    /*RF_Send_Command(CC1120_SRES);
    i = 0;
    while (RF_Get_Status() && i < 1000) {
        Delay_ms(1);
        i++;
    }
    
    printf("Reset in %d ms\n", i);*/
    printf ("Write all config register\n");
    Wait_Transmited();
    i = 0;
    while (i < (sizeof(preferredSettings868)/4)) {
        RF_Write_Reg(preferredSettings868[i][0], preferredSettings868[i][1]);
        i++;
    }
    i--;    
    
    printf ("Last is 0x%04X, 0x%02X\n", preferredSettings868[i][0], preferredSettings868[i][1]);
    
    i = 0;    
    while (i < (sizeof(preferredSettings868)/4)) {
        val8 = RF_Read_Reg(preferredSettings868[i][0]);
        if (val8 != preferredSettings868[i][1]) {
            printf("Error reg 0x%04X : wanted 0x%02X got 0x%02X\r\n", preferredSettings868[i][0], preferredSettings868[i][1], val8);
            Wait_Transmited();
            RF_Write_Reg(preferredSettings868[i][0], preferredSettings868[i][1]);
        }
        i++;
    }
    
    Wait_Transmited();
    printf("Calibration : \n");
    manualCalibration(1);
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
    Wait_Transmited();
    
    // strobe calibration
    RF_Send_Command(CC1120_SCAL);
    Set_Maxtime(1000);
    
    // wait for MARC STATE to be IDLE
    while ( (RF_Read_Reg(CC1120_MARCSTATE) != 0x41) && (!Get_Maxtime()) ) {
        Delay_ms(1);
    }
    if (!Get_Maxtime())
        printf("Maxtime calib 1 !\n");
    
    // read result
    high_FS_VCO2 = RF_Read_Reg(CC1120_FS_VCO2);
    high_FS_VCO4 = RF_Read_Reg(CC1120_FS_VCO4);
    high_FS_CHP = RF_Read_Reg(CC1120_FS_CHP);
    if (verbose)
        printf("Results high : FS_VCO2 : 0x%02X, FS_VCO4 : 0x%02X, FS_CHP : 0x%02X\n", high_FS_VCO2, high_FS_VCO4, high_FS_CHP);
    Wait_Transmited();
    
    // SET VCO CAP ARRAY TO 0 :
    RF_Write_Reg(CC1120_FS_VCO2,0);
    // Re-write with original_fs_cal2
    RF_Write_Reg(CC1120_FS_CAL2, original_fs_cal2);
    Delay_ms (10);
    
    // strobe calibration
    RF_Send_Command(CC1120_SCAL);
    Set_Maxtime(1000);
    
    // wait for MARC STATE to be IDLE
    while ( (RF_Read_Reg(CC1120_MARCSTATE) != 0x41) && (!Get_Maxtime()) ) {
        Delay_ms(1);
    }
    if (!Get_Maxtime())
        printf("Maxtime calib 2 !\n");
    Wait_Transmited();
    
    // read result
    mid_FS_VCO2 = RF_Read_Reg(CC1120_FS_VCO2);
    mid_FS_VCO4 = RF_Read_Reg(CC1120_FS_VCO4);
    mid_FS_CHP = RF_Read_Reg(CC1120_FS_CHP);
    if (verbose)
        printf("Results mid : FS_VCO2 : 0x%02X, FS_VCO4 : 0x%02X, FS_CHP : 0x%02X\n", mid_FS_VCO2, mid_FS_VCO4, mid_FS_CHP);
    Wait_Transmited();
    
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

void RF_Send_Packet_Cmd(void)
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
    
}

void RF_Wait_For_Packet_Cmd(void)
{
    u8 val8, c;
    u8 i, buff;
    u8 last_receive = 1, receive = 0;
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
    
    
    // on reste dans ce mode tant que l'utilisateur n'a pas appuyé sur une touche
    while (!Get_Uart(&c)) {
        //receive = RF_Read_Reg(CC1120_SINGLE_RXFIFO);
        receive = RF_Read_Reg(CC1120_NUM_RXBYTES);
        if (receive) {
            
            buff = RF_Read_Reg(CC1120_SINGLE_RXFIFO);
            printf("0x%02X\r\n", buff);
            
            val8 = RF_Get_Status();
            if (!val8)
                RF_Send_Command(CC1120_SRX);
        }
        
        //if (receive != last_receive) {
            //printf("0x%02X ", receive);
            last_receive = receive;
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
    }
    
    printf("Leaving Receive Mode\n");
}


#define VCDAC_START_OFFSET 2
#define FS_VCO2_INDEX 0
#define FS_VCO4_INDEX 1
#define FS_CHP_INDEX 2

void manualCalibration(u8 verbose) {
  
    u8 original_fs_cal2;
    u8 calResults_for_vcdac_start_high[3];
    u8 calResults_for_vcdac_start_mid[3];
    u8 marcstate;
    u8 writeByte;

    
    // 1) Set VCO cap-array to 0 (FS_VCO2 = 0x00)
    //writeByte = 0x00;
    //cc112xSpiWriteReg(CC112X_FS_VCO2, &writeByte, 1);
    RF_Write_Reg(CC1120_FS_VCO2, 0);
    
    // 2) Start with high VCDAC (original VCDAC_START + 2):
    //cc112xSpiReadReg(CC112X_FS_CAL2, &original_fs_cal2, 1);
    original_fs_cal2 = RF_Read_Reg(CC1120_FS_CAL2);
    printf("original_fs_cal2 %d\r\n", original_fs_cal2);
    Wait_Transmited();
    writeByte = original_fs_cal2 + VCDAC_START_OFFSET;
    //cc112xSpiWriteReg(CC112X_FS_CAL2, &writeByte, 1);
    RF_Write_Reg(CC1120_FS_CAL2, writeByte);
    
    // 3) Calibrate and wait for calibration to be done (radio back in IDLE state)
    //trxSpiCmdStrobe(CC112X_SCAL);
    RF_Send_Command(CC1120_SCAL);
    
    do 
    {
        //cc112xSpiReadReg(CC112X_MARCSTATE, &marcstate, 1);
        marcstate = RF_Read_Reg(CC1120_MARCSTATE);
    } while (marcstate != 0x41);
    
    // 4) Read FS_VCO2, FS_VCO4 and FS_CHP register obtained with high VCDAC_START value
    //cc112xSpiReadReg(CC112X_FS_VCO2, &calResults_for_vcdac_start_high[FS_VCO2_INDEX], 1);
    //cc112xSpiReadReg(CC112X_FS_VCO4, &calResults_for_vcdac_start_high[FS_VCO4_INDEX], 1);
    //cc112xSpiReadReg(CC112X_FS_CHP, &calResults_for_vcdac_start_high[FS_CHP_INDEX], 1);
    calResults_for_vcdac_start_high[FS_VCO2_INDEX] = RF_Read_Reg(CC1120_FS_VCO2);
    calResults_for_vcdac_start_high[FS_VCO4_INDEX] = RF_Read_Reg(CC1120_FS_VCO4);
    calResults_for_vcdac_start_high[FS_CHP_INDEX] = RF_Read_Reg(CC1120_FS_CHP);
    
    printf("calResults_for_vcdac_start_high[FS_VCO2_INDEX] %d\r\n", calResults_for_vcdac_start_high[FS_VCO2_INDEX]);
    Wait_Transmited();
    printf("calResults_for_vcdac_start_high[FS_VCO4_INDEX] %d\r\n", calResults_for_vcdac_start_high[FS_VCO4_INDEX]);
    Wait_Transmited();
    printf("calResults_for_vcdac_start_high[FS_CHP_INDEX] %d\r\n", calResults_for_vcdac_start_high[FS_CHP_INDEX]);
    Wait_Transmited();
         
    // 5) Set VCO cap-array to 0 (FS_VCO2 = 0x00)
    //writeByte = 0x00;
    //cc112xSpiWriteReg(CC112X_FS_VCO2, &writeByte, 1);
    RF_Write_Reg(CC1120_FS_VCO2, 0);
    
    // 6) Continue with mid VCDAC (original VCDAC_START):
    writeByte = original_fs_cal2;
    //cc112xSpiWriteReg(CC112X_FS_CAL2, &writeByte, 1);
    RF_Write_Reg(CC1120_FS_CAL2, writeByte);
    
    // 7) Calibrate and wait for calibration to be done (radio back in IDLE state)
    //trxSpiCmdStrobe(CC112X_SCAL);
    RF_Send_Command(CC1120_SCAL);
    
    do 
    {
        //cc112xSpiReadReg(CC112X_MARCSTATE, &marcstate, 1);
        marcstate = RF_Read_Reg(CC1120_MARCSTATE);
    } while (marcstate != 0x41);
    
    // 8) Read FS_VCO2, FS_VCO4 and FS_CHP register obtained with mid VCDAC_START value
    //cc112xSpiReadReg(CC112X_FS_VCO2, &calResults_for_vcdac_start_mid[FS_VCO2_INDEX], 1);
    //cc112xSpiReadReg(CC112X_FS_VCO4, &calResults_for_vcdac_start_mid[FS_VCO4_INDEX], 1);
    //cc112xSpiReadReg(CC112X_FS_CHP, &calResults_for_vcdac_start_mid[FS_CHP_INDEX], 1);
    
    calResults_for_vcdac_start_mid[FS_VCO2_INDEX] = RF_Read_Reg(CC1120_FS_VCO2);
    calResults_for_vcdac_start_mid[FS_VCO4_INDEX] = RF_Read_Reg(CC1120_FS_VCO4);
    calResults_for_vcdac_start_mid[FS_CHP_INDEX] = RF_Read_Reg(CC1120_FS_CHP);
    
    printf("calResults_for_vcdac_start_mid[FS_VCO2_INDEX] %d\r\n", calResults_for_vcdac_start_mid[FS_VCO2_INDEX]);
    Wait_Transmited();
    printf("calResults_for_vcdac_start_mid[FS_VCO4_INDEX] %d\r\n", calResults_for_vcdac_start_mid[FS_VCO4_INDEX]);
    Wait_Transmited();
    printf("calResults_for_vcdac_start_mid[FS_CHP_INDEX] %d\r\n", calResults_for_vcdac_start_mid[FS_CHP_INDEX]);
    Wait_Transmited();
    
    // 9) Write back highest FS_VCO2 and corresponding FS_VCO and FS_CHP result
    if (calResults_for_vcdac_start_high[FS_VCO2_INDEX] > calResults_for_vcdac_start_mid[FS_VCO2_INDEX]) 
    {
        printf("je prend High\r\n");
        Wait_Transmited();
        writeByte = calResults_for_vcdac_start_high[FS_VCO2_INDEX];
        //cc112xSpiWriteReg(CC112X_FS_VCO2, &writeByte, 1);
        RF_Write_Reg(CC1120_FS_VCO2, writeByte);
        writeByte = calResults_for_vcdac_start_high[FS_VCO4_INDEX];
        //cc112xSpiWriteReg(CC112X_FS_VCO4, &writeByte, 1);
        RF_Write_Reg(CC1120_FS_VCO4, writeByte);
        writeByte = calResults_for_vcdac_start_high[FS_CHP_INDEX];
        //cc112xSpiWriteReg(CC112X_FS_CHP, &writeByte, 1);
        RF_Write_Reg(CC1120_FS_CHP, writeByte);
    }
    else 
    {
        printf("je prend Mid\r\n");
        Wait_Transmited();
        writeByte = calResults_for_vcdac_start_mid[FS_VCO2_INDEX];
        //cc112xSpiWriteReg(CC112X_FS_VCO2, &writeByte, 1);
        RF_Write_Reg(CC1120_FS_VCO2, writeByte);
        writeByte = calResults_for_vcdac_start_mid[FS_VCO4_INDEX];
        //cc112xSpiWriteReg(CC112X_FS_VCO4, &writeByte, 1);
        RF_Write_Reg(CC1120_FS_VCO4, writeByte);
        writeByte = calResults_for_vcdac_start_mid[FS_CHP_INDEX];
        //cc112xSpiWriteReg(CC112X_FS_CHP, &writeByte, 1);
        RF_Write_Reg(CC1120_FS_CHP, writeByte);
    }
}


void Test_Config_SPI_Cmd(void)
{

    
    u16 i, j, config;
    u8 toto;
    u8 SPRE, PPRE;
    u32 nb_errora = 0;
    u32 nb_errorb = 0;
    config = 0;
    for (PPRE = 1; PPRE < 4; PPRE ++) {
        for (SPRE = 3; SPRE < 8; SPRE ++) {

            for (config = 0; config < 8; config ++ ) {
                Delay_ms(2);
                SPI1STATbits.SPIEN = 0;  // desactive le SPI !
                SPI1CON1bits.SPRE = SPRE;
                SPI1CON1bits.PPRE = PPRE;


                SPI1CON1bits.CKP = config & 0x1;
                SPI1CON1bits.CKE = (config >> 1) & 0x1;
                SPI1CON1bits.SMP = (config >> 2) & 0x1;

                nb_errora = 0;
                nb_errorb = 0;

                printf ("Config SPRE %d PPRE %d CKP %d CKE %d SMP %d ", SPI1CON1bits.SPRE, SPI1CON1bits.PPRE, SPI1CON1bits.CKP, SPI1CON1bits.CKE, SPI1CON1bits.SMP);
                
                Delay_ms(2);
                SPI1STATbits.SPIEN = 1;  // active le SPI !
                Delay_ms(2);
                for (j = 0; j < 1000; j++) {
                    /*for (i = 0; i < 255; i++) {
                        RF_Write_Reg(CC1120_SYMBOL_RATE1, i);
                        toto = RF_Read_Reg(CC1120_SYMBOL_RATE1);
                        if (i != toto)
                            nb_errora ++;
                        RF_Write_Reg(CC1120_FREQOFF0, i);
                        toto = RF_Read_Reg(CC1120_FREQOFF0);
                        if (i != toto)
                            nb_errorb ++;
                    }*/
                    i = 0;
                    while (i < (sizeof(preferredSettings868)/4)) {
                        RF_Write_Reg(preferredSettings868[i][0], preferredSettings868[i][1]);
                        i++;
                    }
                    i = 0;    
                    while (i < (sizeof(preferredSettings868)/4)) {
                        toto = RF_Read_Reg(preferredSettings868[i][0]);
                        if (toto != preferredSettings868[i][1]) {
                            nb_errora ++;
                        }
                        i++;
                    }
                }
                printf("%5ld %5ld error\r\n", nb_errora, nb_errorb);
                Wait_Transmited();
           }
        }
     }
    
}