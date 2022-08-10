#include "main.h"


#define Timer_ms1 Compteur_ms_1

#if I2C_MASTER




void Accel_Loop(void)
{
    
}






// void Add_I2C_command(uint8_t i2c_addr, uint8_t nbr_byte_to_send, uint8_t nbr_byte_to_read, uint8_t data_send[], uint8_t data_read[], void *Done)


#endif // I2C_MASTER

/*

void Accel_Init(void)
{
    u8 val8;
    // Configure gyroscope range
    val8 = GYRO_FULL_SCALE_2000_DPS;
    I2C_Write(MPU9250_ADDRESS, 27, 1, &val8);
    // Configure accelerometers range
    val8 = ACC_FULL_SCALE_16_G;
    I2C_Write(MPU9250_ADDRESS, 28, 1, &val8);
    // Set by pass mode for the magnetometers
    val8 = 0x02;
    I2C_Write(MPU9250_ADDRESS, 0x37, 1, &val8);
}

void Accel_Loop (void)
{
    static u32 Last_Timer = 0;
    static u8 Etat_Accel = 0;
    static u8 Max_Time;
    u8 val8;
    u8 Buffer[20];
    
    switch (Etat_Accel) {
        case 0:
            I2C_Read(MPU9250_ADDRESS, 0x3B, 14, &Buffer[0]);
            Etat_Accel = 1;
            break;
        case 1:
            ax = -(Buffer[0]<<8 | Buffer[1]);
            ay = -(Buffer[2]<<8 | Buffer[3]);
            az =   Buffer[4]<<8 | Buffer[5];
            // temp
            temp = Buffer[6]<<8 | Buffer[7];
            // Gyroscope
            gx = -(Buffer[8]<<8 | Buffer[9]);
            gy = -(Buffer[10]<<8 | Buffer[11]);
            gz =   Buffer[12]<<8 | Buffer[13];
            Etat_Accel = 2;
            break;
        case 2:
            val8 = 0x01;
            I2C_Write(MAG_ADDRESS, 0x0A, 1, &val8);
            Max_Time = 0;
            Last_Timer = Compteur_ms_1;
            Etat_Accel = 3;
            break;
        case 3:
            if ((Last_Timer - Compteur_ms_1) > 5) {
                val8 = 0;
                I2C_Read(MAG_ADDRESS, 0x02, 1, &val8);
                if (val8 & 0x01)
                    Etat_Accel = 4;
                else {
                    Last_Timer = Compteur_ms_1;
                    Max_Time ++;
                    if (Max_Time > 10)
                        Etat_Accel = 5;
                }
            }
            break;
        case 4:
            I2C_Read(MAG_ADDRESS,0x03,6,&Buffer[0]);
            // Magnetometer
            mx = -(Buffer[3]<<8 | Buffer[2]);
            my = -(Buffer[1]<<8 | Buffer[0]);
            mz = -(Buffer[5]<<8 | Buffer[4]);
            Etat_Accel = 5;
            Last_Timer = Compteur_ms_1;
            break;
        case 5:
            if ((Last_Timer - Compteur_ms_1) > 20)
                 Etat_Accel = 0;
            break;
        default:
            Etat_Accel = 0;
    }
}

u8 Accel_Print_Cmd (void)
{
    printf ("Accel : \n");
    printf("\tax : %d", ax);
    printf("\tay : %d", ay);
    printf("\taz : %d\n", az);
    Wait_Transmited();

    printf ("Gyro : \n");
    printf("\tgx : %d", gx);
    printf("\tgy : %d", gy);
    printf("\tgz : %d\n", gz);
    Wait_Transmited();

    printf ("Magneto : \n");
    printf("\tmx : %d", mx);
    printf("\tmy : %d", my);
    printf("\tmz : %d\n", mz);
    Wait_Transmited();

    printf("Temp : %d\n",temp);
    Wait_Transmited();
    return 0;
}


     * 
     * /*
     * 
     **/ 
