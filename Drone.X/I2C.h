#ifndef __I2C_H
#define	__I2C_H

#define I2C_MASTER 1


#if I2C_MASTER
    #define I2C_CMD_LIST_SIZE   5
    typedef struct{
        uint8_t i2c_addr;
        uint8_t nbr_byte_to_send;
        uint8_t nbr_byte_to_read;
        uint8_t *data_read;
        uint8_t *data_to_send;
        void *Done;
    }I2C_command;

    void Init_I2C(void);
    void Add_I2C_command(uint8_t i2c_addr, uint8_t nbr_byte_to_send, uint8_t nbr_byte_to_read,uint8_t data_send[], uint8_t data_read[], void *Done);
    void Transmit_I2C_Loop(void);

#define I2C_SCL_PIN     _RB8
#define I2C_SCL_TRIS    _TRISB8
#define I2C_SDA_PIN     _RB9
#define I2C_SDA_TRIS    _TRISB9
    
uint8_t I2C_Wr_Cmd(void);
uint8_t I2C_Rd_Cmd(void);
uint8_t I2C_Wr_Rd_Cmd(void);
void I2C_Stress_Loop (void);
uint8_t I2C_Stress_Cmd(void);

void I2C_Discover_Loop(void);
uint8_t I2C_Discover_Cmd(void);
    
#else
    #define SIZE_BUFF_I2C 5 
    void Init_I2C(void);  
    void Gestion_I2C_Slave_Loop(void);
    
    void Init_I2C_int(void);
    void Gestion_I2C_Slave_int_Loop(void);
    
uint8_t I2C_Wr_Cmd(void);
uint8_t I2C_Rd_Cmd(void);
uint8_t I2C_Wr_Rd_Cmd(void);
uint8_t I2C_Stress_Cmd(void);
#endif


#endif	/* __GESTION_I2C_H */

