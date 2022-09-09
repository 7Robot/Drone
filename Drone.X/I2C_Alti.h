#ifndef __I2C_ALTI_H
#define	__I2C_ALTI_H




#ifdef I2C_MASTER


// csb = gnd
#define ALTI_ADD 0x77       // x2 pour Write, x2+1 pour read
#define ALTI_RESET_CMD 0x1E
#define ALTI_EEPROM_BASE_ADDR 0xA0
#define ALTI_ADC_READ     0x00
#define ALTI_ADC_D1_START 0x48
#define ALTI_ADC_D2_START 0x58

void Alti_Loop(void);
uint8_t Alti_Cmd (void);

#endif // I2C_MASTER




#endif	// __I2C_ACCEL_H

