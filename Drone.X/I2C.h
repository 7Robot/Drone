
#ifndef __I2C_H
#define __I2C_H

// use of I2C1
#define FREQ_I2C 90000  //  50kHz  (norme à 100)

void I2C_Init (void);
void I2C_Try(void);
void I2C_Try_All(void);

// csb = gnd
#define ALTI_ADD 0xEE       // direct pour Write, faire EF pour read
#define ALTI_RESET_CMD 0x1E

void I2C_Alti_Send_Command(u8 command);
u32 I2C_Alti_Read(u8 nb_bytes);

void Alti_Read_EEPROM(void);

// accel add0 = gnd
#define ACCEL_ADD 0xD0      // pour write, faire D1 pour read



#endif