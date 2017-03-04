


#include "main.h"

// ACCEL
int16_t ax, ay, az;
int16_t gx, gy, gz;
int16_t temp;
int16_t mx, my, mz;

void I2C_Init (void)
{
    u16 BRG = 1 + FOSC / (FREQ_I2C * 2);        // calculs simplifiés par rapport à la datasheet, à revoir peut-être
    
    if (BRG > 0x1FF)
        BRG = 0x1FF;    // registre 9 bits !
    
    I2C1BRG = BRG;      // regle le baudrate
    I2C1CONbits.I2CEN = 1;  // active l'interface
}

u8 I2C_Write(u8 add, u8 reg, u8 nb_data, u8 *data)
{
    u8 error = 0;
    Set_Maxtime(10);
    I2C1CONbits.SEN = 1;    // envoi start condition
    while (I2C1CONbits.SEN && Get_Maxtime());    // attente de l'envoi
    I2C1TRN = add<<1;
    Set_Maxtime(30);
    while (!(I2C1STATbits.TRSTAT) && Get_Maxtime());  // attente début transmission
    while (I2C1STATbits.TRSTAT && Get_Maxtime());     // attente fin transmission
    I2C1TRN = reg;
    Set_Maxtime(30);
    while (!(I2C1STATbits.TRSTAT) && Get_Maxtime());  // attente début transmission
    while (I2C1STATbits.TRSTAT && Get_Maxtime());     // attente fin transmission
    while (nb_data) {
        I2C1TRN = *data;
        Set_Maxtime(30);
        while (!(I2C1STATbits.TRSTAT) && Get_Maxtime());  // attente début transmission
        while (I2C1STATbits.TRSTAT && Get_Maxtime());     // attente fin transmission
        data ++;
        nb_data --;
    }
    
    Set_Maxtime(10);
    I2C1CONbits.PEN = 1;    // envoi stop condition
    while (I2C1CONbits.PEN && Get_Maxtime());    // attente de l'envoi
    
    return 0;
}

u8 I2C_Read(u8 add, u8  reg, u8 nb_data, u8 *data)
{
    Set_Maxtime(10);
    I2C1CONbits.SEN = 1;    // envoi start condition
    while (I2C1CONbits.SEN && Get_Maxtime());    // attente de l'envoi
    I2C1TRN = add<<1;
    Set_Maxtime(30);
    while (!(I2C1STATbits.TRSTAT) && Get_Maxtime());  // attente début transmission
    while (I2C1STATbits.TRSTAT && Get_Maxtime());     // attente fin transmission
    I2C1TRN = reg;
    Set_Maxtime(30);
    while (!(I2C1STATbits.TRSTAT) && Get_Maxtime());  // attente début transmission
    while (I2C1STATbits.TRSTAT && Get_Maxtime());     // attente fin transmission
    
    Set_Maxtime(10);
    I2C1CONbits.SEN = 1;    // envoi start condition
    while (I2C1CONbits.SEN && Get_Maxtime());    // attente de l'envoi
    I2C1TRN = (add<<1)+1;
    Set_Maxtime(30);
    while (!(I2C1STATbits.TRSTAT) && Get_Maxtime());  // attente début transmission
    while (I2C1STATbits.TRSTAT && Get_Maxtime());     // attente fin transmission
    
    while (nb_data) {
        nb_data --;
        
        I2C1CONbits.RCEN = 1;   // passage en receive
        Set_Maxtime(30);
        while (I2C1CONbits.RCEN && Get_Maxtime());

        *data = I2C1RCV;
        if (nb_data) {
            data ++;
            I2C1CONbits.ACKDT = 0;      // on veut acknoledge
        } else {
            I2C1CONbits.ACKDT = 1;      // on veut pas acknoledge
        }
        I2C1CONbits.ACKEN = 1;      // laisse partir le bit acknoledge
        while (I2C1CONbits.ACKEN && Get_Maxtime());
    }
    Set_Maxtime(10);
    I2C1CONbits.PEN = 1;    // envoi stop condition
    while (I2C1CONbits.PEN && Get_Maxtime());    // attente de l'envoi

    return 0;
}

void I2C_Try_All_Cmd(void)
{
    
    u16 add;
    for (add = 0x0; add < 0xFF; add += 2)
    {
        I2C1CONbits.I2CEN = 1;  // active l'interface
        Delay_ms(10);
        printf ("\r0x%02X", add);
        Set_Maxtime(30);
        I2C1CONbits.SEN = 1;    // envoi start condition
        while (I2C1CONbits.SEN && Get_Maxtime());    // attente de l'envoi
        if (Get_Maxtime()) {
            I2C1TRN = add;     // write de l'adresse
            while ((!I2C1STATbits.TRSTAT) && Get_Maxtime());  // attente début transmission
            while (I2C1STATbits.TRSTAT && Get_Maxtime());     // attente fin transmission
            if (Get_Maxtime()) {
                if (!I2C1STATbits.ACKSTAT && Get_Maxtime())  // si on a recu un ack :
                {
                    printf (" : found!\n");
                }
            } else {
                printf ("Erreur Transmission\n");
            }
            Set_Maxtime(10);
            I2C1CONbits.PEN = 1;    // envoi stop condition
            while (I2C1CONbits.PEN && Get_Maxtime());    // attente de l'envoi
            if (!Get_Maxtime()) {
                printf ("Erreur Stop\n");
            }
        } else {
            printf ("Erreur Start\n");
        }
        Delay_ms(10);
        I2C1CONbits.I2CEN = 0;  // Désactive l'interface
        Delay_ms(10);
    }
    printf ("Fin\n");
    I2C1CONbits.I2CEN = 1;  // active l'interface
}


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
        EEPROM[i] = val32;
    }
    
}*/

void Alti_Read_Cmd(void)
{
    u8 i;
    u16 EEPROM[8];
    char c;
    u8 tab8[4];
    u32 D1, D2, TEMP, Dt, val32;
    uint64_t val64, OFF, SENS, val64b, PRESS64;
    
    printf("EEPROM\n");
    for (i = 0; i < 8; i++) {
        I2C_Read(ALTI_ADD, 0xA0+2*i, 2, &tab8[0]);
        val32 = (((u16)(tab8[0])) << 8) + tab8[1];
        EEPROM[i] = val32;
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
        
        val32 = EEPROM[5];
        val32 = val32 << 8;
        Dt = D2 - val32;
        
        val64 = Dt;
        val64 = val64 * EEPROM[6];
        val64 = val64 >> 23;
        TEMP = ((u32)(val64)) + 2000; 
        
        
        
        //val64 = ((Dt * EEPROM[6]) / 0x800000) + 2000;

        val64 = Dt;
        val64 = val64 * EEPROM[4];
        val64 = val64 >> 6;
        val64b = EEPROM[2];
        val64b = val64b << 17;
        OFF = val64 + val64b;
        
        val64 = Dt;
        val64 = val64 * EEPROM[3];
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
}



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

void Accel_Print_Cmd (void)
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
}