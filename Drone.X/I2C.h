
#ifndef __I2C_H
#define __I2C_H

// use of I2C1
#define FREQ_I2C 90000  //  50kHz  (norme à 100)

void I2C_Init (void);
u8 I2C_Try_All_Cmd(void);

// csb = gnd
#define ALTI_ADD 0x77       // x2 pour Write, x2+1 pour read
#define ALTI_RESET_CMD 0x1E

//void I2C_Alti_Send_Command(u8 command);
//u32 I2C_Alti_Read(u8 nb_bytes);

u8 I2C_Write(u8 add, u8 reg, u8 nb_data, u8 *data);
u8 I2C_Read(u8 add, u8  reg, u8 nb_data, u8 *data);

u8 Alti_Read_Cmd(void);

// accel add0 = gnd
#define ACCEL_ADD 0x68      // x2 pour Write, x2+1 pour read

#define    MPU9250_ADDRESS            0x68
#define    MAG_ADDRESS                0x0C
 
#define    GYRO_FULL_SCALE_250_DPS    0x00  
#define    GYRO_FULL_SCALE_500_DPS    0x08
#define    GYRO_FULL_SCALE_1000_DPS   0x10
#define    GYRO_FULL_SCALE_2000_DPS   0x18
 
#define    ACC_FULL_SCALE_2_G        0x00  
#define    ACC_FULL_SCALE_4_G        0x08
#define    ACC_FULL_SCALE_8_G        0x10
#define    ACC_FULL_SCALE_16_G       0x18


u8 I2C_Try_Accel_Cmd (void);


void Accel_Init(void);
void Accel_Loop (void);
u8 Accel_Print_Cmd (void);

#endif