
#ifndef __I2C_H
#define __I2C_H


void I2C_Init (void);

#define ALTI_ADD 0x77       // 7 bits de poids fort // faire x2 pour write et x2+1 pour read
#define ALTI_RESET_CMD 0x1E

#endif