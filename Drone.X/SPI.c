


#include "main.h"


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
   
   
   SPI1STATbits.SPIEN = 0;  // desactive le SPI !
   
   
   SPI1CON1bits.MODE16 = 0; // mode 8 bits
   SPI1CON1bits.SMP = 1;    // latch de la data in à la fin de la présence de data out
   //SPI1CON1bits.CKP = 0;    // clk repos = 0, clk active = 1
   //SPI1CON1bits.CKE = 1;    // change la data quand la clock passe de active à repos (de 1 à 0)
   SPI1CON1bits.CKP = 1;
   SPI1CON1bits.CKE = 0;
   SPI1CON1bits.MSTEN = 1;  //  mode master 
   
   SPI1CON1bits.PPRE = 1;   // prim precale à 1/4
   SPI1CON1bits.SPRE = 2;   // second prescale à 1/4
   // =>  1/16 depuis la clock principale (40MHz))     => 2.5MH
   
   SPI1STATbits.SPIEN = 1;  // active le SPI !
   
   titi = SPI1BUF;
      
}

u8 SPI_Access (u8 val_send)
{
    SPI1BUF = val_send;
    while (!SPI1STATbits.SPIRBF);
    return SPI1BUF;
}

