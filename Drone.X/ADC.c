
#include "main.h"



void ADC_Init(void)
{

    //Configuration du convertisseur Analog to Digital (ADC) du dspic33f
    //Cf page 286 dspic33f Data Sheet
    
    
    
    //AD1CON1 Configuration
    AD1CON1bits.ADON = 0;    //Eteindre A/D converter pour la configuration
    AD1CON1bits.FORM = 0;    //Configure le format de la sortie de l'ADC ( 3=signed float, 2=unsigned float, 1=signed integer, 0=unsigned integer
    AD1CON1bits.SSRC = 7;    //Config de l'Ã©chantillonnage : compteur interne
    AD1CON1bits.SIMSAM = 0;  //Simultaneously Sample CH0
    AD1CON1bits.ASAM = 0;    //DÃ©but d'Ã©chantillonnage (1=tout de suite  0=dÃ¨s que AD1CON1bits.SAMP est activÃ©)
    AD1CON1bits.AD12B = 0;   //Choix du type de converter (10 ou 12 bits) 0 = 10 bits , 1 = 12bits

    //AD1CON2 Configuration
    AD1CON2bits.VCFG = 0;       // par defaut = converti entre 0 et VCC
    AD1CON2bits.ALTS = 0;     //Always sampling on channel A
    AD1CON2bits.CHPS = 0;    //Select CH0
    
    //AD1CON3 Configuration
    AD1CON3bits.ADRC = 1;        //Choix du type de clock interne ADC (=1) ou generée par FCY (=0)
    AD1CON3bits.ADCS = 10;      // auto sample time
    
    //Choix des rÃ©fÃ©rences de tensions
                                                        // Choix du (+) de la mesure pour le channel CH0, commenÃ§ant par le sick 1
    AD1CHS0bits.CH0SA = ADC_CHAN_VBAT;
    AD1CHS0bits.CH0NA = 0;	// Choix du (-) de la mesure pour le channel CH0 (0 = Masse interne pic)

   

    //Configuration des pins analogiques
    AD1PCFGL = 0xFFFF;   //Met tous les ports AN en Digital Input
    // mets les 2 entrés intéressantes en analogique
    // vbat :
    AD1PCFGLbits.PCFG0 = 0;
    // sense 5V
    AD1PCFGLbits.PCFG1 = 0;
    
    
    
    AD1CON1bits.SAMP = 0;
    AD1CON1bits.ADON = 1;    // Turn on the A/D converter
}




u16 ADC_Convert(u8 chan)
{
    AD1CHS0bits.CH0SA = chan;
    AD1CON1bits.SAMP = 1;   // début du temps de sample, qui convetira tout seul après
    
    Maxtime = 100;   // 100 ms pour la conversion max  (bien trop))
    // attente de la conversion
    while ((!AD1CON1bits.DONE) && (Maxtime));
    
    if (AD1CON1bits.DONE)
        return ADC1BUF0;
    else {
        printf("error");
        return 0xFFFF;
    }
}

