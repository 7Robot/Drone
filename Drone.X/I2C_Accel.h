#ifndef __I2C_ACCEL_H
#define	__I2C_ACCEL_H




#ifdef I2C_MASTER

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




void Accel_Loop(void);

#endif // I2C_MASTER




#endif	// __I2C_ACCEL_H

