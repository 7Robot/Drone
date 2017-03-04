


#include "main.h"


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
