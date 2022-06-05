#ifndef __GESTION_I2C_H
#define	__GESTION_I2C_H

#define I2C_MASTER 0


#if I2C_MASTER
    #define I2C_CMD_LIST_SIZE   5
    typedef struct{
        uint8_t i2c_addr;
        uint8_t nbr_byte_send;
        uint8_t nbr_byte_read;
        uint8_t *data_read;
        uint8_t *data_send;
        void *Done;
    }I2C_command;

    void Init_I2C(void);
    void Add_I2C_command(uint8_t i2c_addr, uint8_t nbr_byte_send, uint8_t nbr_byte_read,uint8_t data_send[], uint8_t data_read[], void *Done);
    void Transmit_I2C_Loop(void);

#else
    #define SIZE_BUFF_I2C 5 
    void Init_I2C(void);  
    void Gestion_I2C_Slave_Loop(void);
#endif


#endif	/* __GESTION_I2C_H */

