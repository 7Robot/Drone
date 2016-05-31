

#include "main.h"



void Init_Clk(void)
{
    u8 i = 0;
    
    do { i++; } while (i);
    
    // Configure PLL prescaler, PLL postscaler, PLL divisor
    PLLFBDbits.PLLDIV = 150;        // M=152
    //PLLFBDbits.PLLDIV = 98;         //  M = 100
    CLKDIVbits.PLLPRE  = 5;         // N1=7
    CLKDIVbits.PLLPOST = 0;         // N2=2
    //CLKDIVbits.PLLPOST = 3;         // N2=8
    
    // Fosc = M/(N1.N2)*Fin
    // Fin : 7.37MHz (quartz interne)
    // Fosc voulue à 80 MHZ (ne doit pas dépasser 80 MHZ)
    // la solution la plus proche est 152*7.37/(7*2) = 80.017
    // attention, cela entraine donc une FCY et une FPériphériques à 40 MHZ
    
    // si M = 151 => 151*7.37/(7*2) = 79.491
    
    while (!OSCCONbits.LOCK);       // attente que la PLL soit lockée sur se nouvelle configuration.
    
    i = 0;
    do { i++; } while (i);
    
}

// vieux code pour passer de sans la PLL à avec :
//    __builtin_write_OSCCONH(0x78);  
//    __builtin_write_OSCCONH(0x9A);
//    __builtin_write_OSCCONH(0x01);
//    //OSCCONH = 1;        //  choix de la PLL avec FRC en entrée de la PLL
//    __builtin_write_OSCCONL(0x46);  
//    __builtin_write_OSCCONL(0x57);
//    __builtin_write_OSCCONL(0x01);
    //OSCCONL = 1;        // active le changement de clock
    
    //while (OSCCONbits.OSWEN);       // attend la fin du changement