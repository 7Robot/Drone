


#include "main.h"


void I2C_Init (void)
{
    u16 BRG = 1 + FOSC / (FREQ_I2C * 2);        // calculs simplifiés par rapport à la datasheet, à revoir peut-être
    
    if (BRG > 0x1FF)
        BRG = 0x1FF;    // registre 9 bits !
    
    I2C1BRG = BRG;      // regle le baudrate
    I2C1CONbits.I2CEN = 1;  // active l'interface
    
}

void I2C_Try(void)
{
    u8 val8;
    printf("Test alti \n");
    Maxtime = 10;
    I2C1CONbits.SEN = 1;    // envoi start condition
    while (I2C1CONbits.SEN && Maxtime);    // attente de l'envoi
    I2C1TRN = ALTI_ADD;     // write
    Maxtime = 30;
    while ((!I2C1STATbits.TRSTAT) && Maxtime);  // attente début transmission
    while (I2C1STATbits.TRSTAT && Maxtime);     // attente fin transmission
    
    if (!I2C1STATbits.ACKSTAT && Maxtime)  // si on a bien reçu l'acknoledge de l'atltimetre
    {
        I2C1TRN = ALTI_RESET_CMD;
        Maxtime = 30;
        while ((!I2C1STATbits.TRSTAT) && Maxtime);  // attente début transmission
        while (I2C1STATbits.TRSTAT && Maxtime);     // attente fin transmission
        if (!I2C1STATbits.ACKSTAT && Maxtime)  // si on a bien reçu l'acknoledge de l'atltimetre
        {
            printf("Alti OK !\n");
            
        } else {
            printf ("Cmd Failed\n");
        }
    } else {
        printf ("Add failed\n");
    }
    Maxtime = 10;
    I2C1CONbits.PEN = 1;    // envoi stop condition
    while (I2C1CONbits.PEN && Maxtime);    // attente de l'envoi
    
    Delay_ms(50);   // petite pause!
     printf("Test accel \n");
    Maxtime = 10;
    I2C1CONbits.SEN = 1;    // envoi start condition
    while (I2C1CONbits.SEN && Maxtime);    // attente de l'envoi
    I2C1TRN = ACCEL_ADD;     // write
    Maxtime = 30;
    while ((!I2C1STATbits.TRSTAT) && Maxtime);  // attente début transmission
    while (I2C1STATbits.TRSTAT && Maxtime);     // attente fin transmission
    
    if (!I2C1STATbits.ACKSTAT && Maxtime)  // si on a bien reçu l'acknoledge de l'accel
    {
        I2C1TRN = 0x71;     //registre "who am I"
        Maxtime = 30;
        while ((!I2C1STATbits.TRSTAT) && Maxtime);  // attente début transmission
        while (I2C1STATbits.TRSTAT && Maxtime);     // attente fin transmission
        if (!I2C1STATbits.ACKSTAT && Maxtime)  // si on a bien reçu l'acknoledge de l'atltimetre
        {
            Maxtime = 100;
            I2C1CONbits.SEN = 1;    // envoi start condition
            while (I2C1CONbits.SEN && Maxtime);    // attente de l'envoi
            I2C1TRN = ACCEL_ADD+1;     // read !
            while ((!I2C1STATbits.TRSTAT) && Maxtime);  // attente début transmission
            while (I2C1STATbits.TRSTAT && Maxtime);     // attente fin transmission
            
            I2C1CONbits.RCEN = 1;   // passage en receive
            while (I2C1CONbits.RCEN && Maxtime);
            val8 = I2C1RCV;
            I2C1CONbits.ACKDT = 1;      // on veut pas acknoledge
            I2C1CONbits.ACKEN = 1;      // laisse partir le bit acknoledge
            
            while (I2C1CONbits.ACKEN && Maxtime);
            
            
            I2C1CONbits.PEN = 1;    // envoi stop condition
            while (I2C1CONbits.PEN && Maxtime);    // attente de l'envoi
            if (!Maxtime) {
                printf ("error Rd\n");
            } else {
                printf("Accel OK, who am I is : 0x%02X", val8);
            }
            
        } else {
            printf ("Reg add write Failed\n");
        }
    } else {
        printf ("Add failed\n");
    }
    
    
}


void I2C_Try_All(void)
{
    
    u8 add;
    for (add = 0; add < 0xFF; add ++)
    {
        Maxtime = 30;
        I2C1CONbits.SEN = 1;    // envoi start condition
        while (I2C1CONbits.SEN && Maxtime);    // attente de l'envoi
        I2C1TRN = add;     // write de l'adresse
        while ((!I2C1STATbits.TRSTAT) && Maxtime);  // attente début transmission
        while (I2C1STATbits.TRSTAT && Maxtime);     // attente fin transmission

        if (!I2C1STATbits.ACKSTAT && Maxtime)  // si on a recu un ack :
        {
            printf ("found : 0x%02X\n", add);
        }
        Maxtime = 10;
        I2C1CONbits.PEN = 1;    // envoi stop condition
        while (I2C1CONbits.PEN && Maxtime);    // attente de l'envoi
        Delay_ms(10);
    }
    printf ("Fin\n");
}

void I2C_Alti_Send_Command(u8 command)
{
    Maxtime = 40;
    I2C1CONbits.SEN = 1;    // envoi start condition
    while (I2C1CONbits.SEN && Maxtime);    // attente de l'envoi
    I2C1TRN = ALTI_ADD;     // write
    while ((!I2C1STATbits.TRSTAT) && Maxtime);  // attente début transmission
    while (I2C1STATbits.TRSTAT && Maxtime);     // attente fin transmission
    
        
    I2C1TRN = command;
    while ((!I2C1STATbits.TRSTAT) && Maxtime);  // attente début transmission
    while (I2C1STATbits.TRSTAT && Maxtime);     // attente fin transmission

    I2C1CONbits.PEN = 1;    // envoi stop condition
    while (I2C1CONbits.PEN && Maxtime);    // attente de l'envoi
    // if (!Maxtime)
    //    printf ("error Cmd\n");
}

u32 I2C_Alti_Read(u8 nb_bytes)
{
    u8 i;
    u32 val32 = 0;
    Maxtime = 40;
    I2C1CONbits.SEN = 1;    // envoi start condition
    while (I2C1CONbits.SEN && Maxtime);    // attente de l'envoi
    I2C1TRN = ALTI_ADD+1;     // read
    while ((!I2C1STATbits.TRSTAT) && Maxtime);  // attente début transmission
    while (I2C1STATbits.TRSTAT && Maxtime);     // attente fin transmission
    
    for (i = 1; i <= nb_bytes; i ++) {
        I2C1CONbits.RCEN = 1;   // passage en receive
        while (I2C1CONbits.RCEN && Maxtime);
        
        val32 = (val32 * 256) + I2C1RCV;
        
        if (i == nb_bytes)
            I2C1CONbits.ACKDT = 1;      // on veut pas acknoledge
        else
            I2C1CONbits.ACKDT = 0;      // on veut acknoledge
            
        I2C1CONbits.ACKEN = 1;      // laisse partir le bit acknoledge
        while (I2C1CONbits.ACKEN && Maxtime);
    }
    
    I2C1CONbits.PEN = 1;    // envoi stop condition
    while (I2C1CONbits.PEN && Maxtime);    // attente de l'envoi
    if (!Maxtime)
        printf ("error Rd\n");
    return val32;
}



void Alti_Read_EEPROM(void)
{
    u8 i;
    char c;
    u16 EEPROM[8];
    u32 D1, D2, TEMP, Dt, val32;
    uint64_t val64, OFF, SENS, val64b, PRESS64;
    printf("EEPROM\n");
    for (i = 0; i < 8; i++)
    {
        I2C_Alti_Send_Command(0xA0 + 2*i);
        val32 = I2C_Alti_Read(2);
        EEPROM[i] = val32;
        printf("0x%04lX\n", val32 );
        Delay_ms(50);
    }
    /*u8 CRC_Rd = EEPROM[7];
    EEPROM[7] = EEPROM[7] & 0xFF00;
    u8 n_bit, cnt, val8;
    u16 n_rem;
    for (cnt = 0; cnt < 16; cnt ++) {
        if (cnt & 0x01) {
            val8 = EEPROM[cnt/2] & 0x00FF;
        } else {
            val8 = EEPROM[cnt/2] >> 8;
        }
        n_rem ^= val8;
        for (n_bit = 0; n_bit < 8; n_bit ++) {
            if (n_rem & 0x8000) {
                n_rem = (n_rem * 2) ^ 0x3000;
            } else {
                n_rem *= 2;
            }
        }
        //printf ("n_rem : 0x%04X\n", n_rem);
        //Delay_ms(10);
    }*/
    
    
    
    printf("Convert_pressions et temp\n");
    while (!(Get_Uart(&c)))
    {
        D1 = 0;
        D2 = 0;
        //for (i = 0; i < 20; i++) {
        for (i = 0; i < 5; i++) {
            I2C_Alti_Send_Command(0x48);
            Delay_ms(11);
            I2C_Alti_Send_Command(0);   // read
            D1 += I2C_Alti_Read(3);
            I2C_Alti_Send_Command(0x58);
            Delay_ms(11);
            I2C_Alti_Send_Command(0);   // read
            D2 += I2C_Alti_Read(3);
        }
        
        while(!Is_TX_Empty());
        
        D1 = D1 / 5;
        D2 = D2 / 5;
        
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
        printf("\rTemp %ld", TEMP);
        printf(" Press  %lld", PRESS64);
    }
}