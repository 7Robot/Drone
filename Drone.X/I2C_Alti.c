#include "main.h"



#ifdef I2C_MASTER

uint8_t crc4(uint16_t n_prom[]);

uint16_t Alti_EEPROM[8];

uint8_t Alti_State = 0;
uint8_t Alti_Done_Poubelle = 1;
uint8_t Alti_Done = 1;
uint8_t Alti_I2C_Cmd;
uint16_t Alti_Last_Timer = 0;

uint32_t Alti_D1, Alti_D2;
uint8_t Alti_D1_Tab[3];
uint8_t Alti_D2_Tab[3];

void Alti_Loop(void)
{
    if (Alti_State) {
        if (Alti_Done) {
            
            if (Alti_State == 1) {
                Alti_Last_Timer = Timer_ms1;
                Alti_I2C_Cmd = ALTI_RESET_CMD;
                Alti_Done = 0;
                Add_I2C_command(ALTI_ADD, 1, 0, &Alti_I2C_Cmd, NULL, &Alti_Done);
                Alti_State ++;
            } else if (Alti_State == 2) {
                if ((Timer_ms1 - Alti_Last_Timer) > 100) {
                    Alti_State = 10;
                }
                uint8_t i;
                for (i = 0; i < 8; i++) {
                    Alti_EEPROM[i] = 0;
                }
            } else if (Alti_State < 18) {
                Alti_I2C_Cmd = ALTI_EEPROM_BASE_ADDR + 2*(Alti_State - 10);
                printf("Read in 0x%02X\n", Alti_I2C_Cmd);
                Alti_Done = 0;
                Add_I2C_command(ALTI_ADD, 1, 0, &Alti_I2C_Cmd, NULL,                       &Alti_Done_Poubelle);
                Add_I2C_command(ALTI_ADD, 0, 2, NULL,         &Alti_EEPROM[Alti_State-10], &Alti_Done);
                Alti_State ++;
            } else if (Alti_State == 18) {
                uint8_t i;
                Alti_State = 20;
                for (i = 0; i < 8; i++) {
                    Alti_EEPROM[i] = (Alti_EEPROM[i] >> 8) + (Alti_EEPROM[i] << 8);
                    printf("0x%04X\n", Alti_EEPROM[i]);
                }
                /*
                crc4(Alti_EEPROM);
                for (i = 0; i < 8; i++) {
                    uint16_t val16a = Alti_EEPROM[i];
                    uint16_t val16b = 0;
                    int j;
                    for (j = 0; j < 16; j ++) {
                        val16b = val16b << 1;
                        val16b |= val16a & 0x0001;
                        val16a = val16a >> 1;
                    }
                    //Alti_EEPROM[i] = (Alti_EEPROM[i] >> 8) + (Alti_EEPROM[i] << 8);
                    Alti_EEPROM[i] = val16b;
                }
                for (i = 0; i < 8; i++) {
                    printf("0x%04X\n", Alti_EEPROM[i]);
                }
                crc4(Alti_EEPROM);
                uint16_t test_prom[] = {0x3132,0x3334,0x3536,0x3738,0x3940,0x4142,0x4344,0x4500};
                crc4(test_prom);
                */
            } else if (Alti_State == 20) {
                Alti_I2C_Cmd = ALTI_ADC_D1_START;
                Alti_Done = 0;
                Add_I2C_command(ALTI_ADD, 1, 0, &Alti_I2C_Cmd, NULL, &Alti_Done);
                Alti_Last_Timer = Timer_ms1;
                Alti_State ++;
            } else if (Alti_State == 21) {
                if ((Timer_ms1 - Alti_Last_Timer) > 100) {
                    Alti_I2C_Cmd = ALTI_ADC_READ;
                    Alti_D1 = 0;
                    Alti_Done = 0;
                    Add_I2C_command(ALTI_ADD, 1, 3, &Alti_I2C_Cmd, &Alti_D1,    &Alti_Done);
                    Alti_State = 30;
                }
            } else if (Alti_State == 30) {
                Alti_I2C_Cmd = ALTI_ADC_D2_START;
                Alti_Done = 0;
                Add_I2C_command(ALTI_ADD, 1, 0, &Alti_I2C_Cmd, NULL, &Alti_Done);
                Alti_Last_Timer = Timer_ms1;
                Alti_State ++;
            } else if (Alti_State == 31) {
                if ((Timer_ms1 - Alti_Last_Timer) > 100) {
                    Alti_I2C_Cmd = ALTI_ADC_READ;
                    Alti_D2 = 0;
                    Alti_Done = 0;
                    Add_I2C_command(ALTI_ADD, 1, 3, &Alti_I2C_Cmd, &Alti_D2,    &Alti_Done);
                    //Add_I2C_command(ALTI_ADD, 1, 0, &Alti_I2C_Cmd, NULL,    &Alti_Done_Poubelle);
                    //Add_I2C_command(ALTI_ADD, 0, 1, NULL,         &Alti_D2_Tab, &Alti_Done);
                    //Add_I2C_command(ALTI_ADD, 0, 1, NULL,         &Alti_D2, &Alti_Done);
                    Alti_State = 40;
                }
            } else if (Alti_State == 40) {
                /*printf("%02X", Alti_D1_Tab[0]);
                printf("%02X", Alti_D1_Tab[1]);
                printf("%02X\n", Alti_D1_Tab[2]);
                
                printf("%02X", Alti_D2_Tab[0]);
                printf("%02X", Alti_D2_Tab[1]);
                printf("%02X\n", Alti_D2_Tab[2]);*/
                
                
                Alti_D1 = ((Alti_D1 & 0x0000FF) << 16) + ((Alti_D1 & 0x00FF00)) + ((Alti_D1 & 0xFF0000) >> 16);
                Alti_D2 = ((Alti_D2 & 0x0000FF) << 16) + ((Alti_D2 & 0x00FF00)) + ((Alti_D2 & 0xFF0000) >> 16);
                
                printf("D1 %lX\n", Alti_D1);
                printf("D2 %lX\n", Alti_D2);
                
                uint32_t C5 = Alti_EEPROM[5];
                C5 = C5 << 8;
                
                int32_t Dt = Alti_D2 - C5;
                float TempSens = Alti_EEPROM[6];
                int i;
                for (i = 0; i < 23; i ++) { // / 2¨23
                    TempSens = TempSens / 2.0;
                }
                float Temp = (Dt * TempSens) + 2000;
                Temp = Temp / 100.0;
                printf("Temp %.3f\n", Temp);
                Alti_State = 0;
            }
        }
    }
}


uint8_t crc4(uint16_t n_prom[])
{
    int cnt; // simple counter
    uint16_t n_rem; // crc reminder
    uint16_t crc_read; // original value of the crc
    uint8_t n_bit;
    
    n_rem = 0x00;
    crc_read = n_prom[7]; //save read CRC
    printf("Read is %02X\n", crc_read);
    n_prom[7] = (0xFF00 & (n_prom[7])); //CRC byte is replaced by 0
    
     // operation is performed on bytes
    for (cnt = 0; cnt < 16; cnt++) { // choose LSB or MSB
        if (cnt & 1) {
            n_rem ^= (uint16_t) ((n_prom[cnt>>1]) & 0x00FF);
        } else {
            n_rem ^= (uint16_t) (n_prom[cnt>>1]>>8);
        }
        
        for (n_bit = 8; n_bit > 0; n_bit--) {
            if (n_rem & (0x8000)) {
                n_rem = (n_rem << 1) ^ 0x3000;
            } else {
                n_rem = (n_rem << 1);
            }
        }
    }
    n_rem = (0x000F & (n_rem >> 12)); // final 4-bit reminder is CRC code
    n_prom[7] = crc_read; // restore the crc_read to its original place
    
    printf("Calculated is %02X\n", n_rem);
    return (n_rem ^ 0x0);
}




uint8_t Alti_Cmd (void)
{
    Alti_Done = 1;
    Alti_State = 1;
    return 0;
}




// void Add_I2C_command(uint8_t i2c_addr, uint8_t nbr_byte_to_send, uint8_t nbr_byte_to_read, uint8_t data_send[], uint8_t data_read[], void *Done)


#endif // I2C_MASTER



    /*
void Alti_Init (void)
{    
    u16 EEPROM[8];
    u8 i;
    u8 tab8[2];
    u32 val32;
    for (i = 0; i < 8; i++) {
        I2C_Read(ALTI_ADD, 0xA0+2*i, 2, &tab8[0]);
        val32 = (((u16)(tab8[0])) << 8) + tab8[1];
        Alti_EEPROM[i] = val32;
    }
    
}

u8 Alti_Read_Cmd(void)
{
    u8 i;
    u16 Alti_EEPROM[8];
    char c;
    u8 tab8[4];
    u32 D1, D2, TEMP, Dt, val32;
    uint64_t val64, OFF, SENS, val64b, PRESS64;
    
    printf("EEPROM\n");
    for (i = 0; i < 8; i++) {
        I2C_Read(ALTI_ADD, 0xA0+2*i, 2, &tab8[0]);
        val32 = (((u16)(tab8[0])) << 8) + tab8[1];
        Alti_EEPROM[i] = val32;
        printf("0x%04lX\n", val32 );
        Delay_ms(50);
    }    
    printf("EEPROM\n");
    for (i = 0; i < 8; i++) {
        I2C_Read(ALTI_ADD, 0xA0+2*i, 2, &val32);
        printf("0x%04lX\n", val32 );
        Delay_ms(50);
    }
    
    
    printf("Convert_pressions et temp\n");
    while (!(Get_Uart(&c)))
    {
        D1 = 0;
        D2 = 0;
        //for (i = 0; i < 20; i++) {
        for (i = 0; i < 25; i++) {
            I2C_Write(ALTI_ADD, 0x48 ,0 ,0);
            //I2C_Alti_Send_Command(0x48);
            Delay_ms(11);
            I2C_Read(ALTI_ADD, 0, 3, &tab8[0]);
            D1 += (((u32)(tab8[0])) << 16) + (((u16)(tab8[1])) << 8) + tab8[2];
            
            I2C_Write(ALTI_ADD, 0x58 ,0 ,0);
            //I2C_Alti_Send_Command(0x58);
            Delay_ms(11);
            I2C_Read(ALTI_ADD, 0, 3, &tab8[0]);
            D2 += (((u32)(tab8[0])) << 16) + (((u16)(tab8[1])) << 8) + tab8[2];
        }
        
        while(!Is_TX_Empty());
        
        D1 = D1 / 25;
        D2 = D2 / 25;
        
        val32 = Alti_EEPROM[5];
        val32 = val32 << 8;
        Dt = D2 - val32;
        
        val64 = Dt;
        val64 = val64 * Alti_EEPROM[6];
        val64 = val64 >> 23;
        TEMP = ((u32)(val64)) + 2000; 
        
        
        
        //val64 = ((Dt * Alti_EEPROM[6]) / 0x800000) + 2000;

        val64 = Dt;
        val64 = val64 * Alti_EEPROM[4];
        val64 = val64 >> 6;
        val64b = Alti_EEPROM[2];
        val64b = val64b << 17;
        OFF = val64 + val64b;
        
        val64 = Dt;
        val64 = val64 * Alti_EEPROM[3];
        val64 = val64 >> 7;
        val64b = EEPROM[1];
        val64b = val64b << 16;
        SENS = val64 + val64b;
        
        val64 = D1;
        val64 = D1 * SENS;
        val64 = val64 >> 21;
        val64 = val64 - OFF;
        PRESS64 = val64 >> 15;
        
        
        //printf("0x%06lX  0x%06lX\r", val32, val32b);
        //printf("D2 0x%08lX Dt 0x%08lX  Temp %ld\n", D2, Dt, TEMP);
        //printf("D1 0x%06lX OFF 0x%016llX  SENS 0x%016llX  Press  %lld\n", D1, OFF, SENS, PRESS64);
        printf("\rTemp %ld.%ld", (TEMP/100), (TEMP%100));
        printf(" Press  %lld  ", PRESS64);
    }
    return 0;
}


*/