


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

u8 RF_Reset_Cmd(void)
{
    if (RF_Reset_Actif) {
        SPI_Init();
        printf ("Active RF\n");
    } else {
        printf ("Desactive RF\n");
    }
    RST_RF = RF_Reset_Actif;
    RF_Reset_Actif = !RF_Reset_Actif;
    return 0;
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

u8 RF_Init_Cmd (void)
{
    u16 i;
    u8 val8;
    
    RF_Reset_Actif = 0;
    RST_RF = 1;
    
    SPI_Init();
    
    Delay_ms(100);
    printf("Reset de la carte RF\n");
    Wait_Transmited();
    RF_Send_Command(CC1120_SRES);
    i = 0;
    while (RF_Get_Status() && i < 1000) {
        Delay_ms(1);
        i++;
    }
    
    printf("Reset in %d ms\n", i);
    
    printf ("Write all config register\n");
    Wait_Transmited();
    
    for (i = 0; i < (sizeof(preferredSettings868)/4); i++) {
        RF_Write_Reg(preferredSettings868[i][0], preferredSettings868[i][1]);
    }
    
    
    Wait_Transmited();
    printf("Calibration : \n");
    manualCalibration(1);
    printf ("RF is working\n");
    return 0;
}


void RF_Add_FIFO_TX(u8 Data)
{
    RF_Write_Reg(CC1120_SINGLE_TXFIFO, Data);
}

void RF_FIFO_TX_Send (void)
{
    u8 Nb_Data;
    Nb_Data = RF_Read_Reg(CC1120_NUM_TXBYTES);
    RF_Write_Reg(CC1120_PKT_LEN, Nb_Data);  // change le nombre de données à envoyer
    RF_Send_Command(CC1120_STX);
}

u8 RF_Still_Transmitting (void)
{
    return (RF_Get_Status() != CC1120_STATE_IDLE);
}

u8 RF_In_Error (void)
{
    u8 val8 = RF_Get_Status();
    return ((val8 == CC1120_STATE_RXFIFO_ERROR) ||(val8 == CC1120_STATE_TXFIFO_ERROR) );
}

u8 RF_Get_FIFO_RX (void)
{
    return RF_Read_Reg(CC1120_SINGLE_RXFIFO);
}

u8 RF_Get_Nb_Data_FIFO_RX (void)
{
    return RF_Read_Reg(CC1120_NUM_RXBYTES);
}

void RF_Set_RX_Mode(void)
{
    RF_Send_Command(CC1120_SRX);
}
