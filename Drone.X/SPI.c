


#include "main.h"


u8 RF_Reset_Actif = 1;

void SPI_Init(void)
{
    u16 titi;
// SPI MISO RB2     = RP2       // in
// SPI MOSI RB1     = RP1       // out
// SPI SCLK RB0     = RP0       // out
    
   _RP0R = 0b01000;     // SPI1 clk
   _SCK1R = 0;
   _RP1R = 0b00111;     // SPI data out
   _SDI1R = 2;
   
   
   
   SPI1CON1bits.MODE16 = 0; // mode 8 bits
   SPI1CON1bits.SMP = 0;    // latch de la data in au milieu de la présence de data out
   SPI1CON1bits.CKP = 0;    // clk repos = 0, clk active = 1
   SPI1CON1bits.CKE = 1;    // change la data quand la clock passe de active à repos (de 1 à 0)
   SPI1CON1bits.MSTEN = 1;  //  mode master 
   
   SPI1CON1bits.PPRE = 0;   // prim precale à 1/64
   SPI1CON1bits.SPRE = 0;   // second prescale à 1/8
   // =>  1/512 depuis la clock principale (40MHz))     => 78 kHz
   
   SPI1STATbits.SPIEN = 1;  // active le SPI !
   
   titi = SPI1BUF;
      
}



void RF_Reset(void)
{
    if (RF_Reset_Actif) {
        printf ("Active RF\n");
    } else {
        printf ("Desactive RF\n");
    }
    RST_RF = RF_Reset_Actif;
    RF_Reset_Actif = !RF_Reset_Actif;
}

void RF_Try(void)
{
    u16 totoa, totob;
    u8 i;
    for (i = 0; i < 0x30; i++) {
        CSN_RF = 0;
        SPI1BUF = 0x80 | i;
        Maxtime = 20;
        while ((!SPI1STATbits.SPIRBF) && Maxtime);
        totoa = SPI1BUF;
        SPI1BUF = 0;    // write vierge pour faire le transfert !
        Maxtime = 20;
        while ((!SPI1STATbits.SPIRBF) && Maxtime);
        totob = SPI1BUF;
        
        CSN_RF = 1;
        printf ("read 0x%02X :  stat 0x%02X  reg 0x%02X\n", i, totoa, totob);
        Delay_ms(10);
    }
}