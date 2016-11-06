
#include "main.h"

volatile float V_5V = 5.0;
volatile float V_Vbat = 5.0;

u8 Last_ADC_Convert = ADC_CHAN_VBAT;
//u8 Error_ADC = 0; // pour débug

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
    
    AD1CON1bits.DONE = 0;   // clear du Done si nécessaire
    AD1CON1bits.SAMP = 1;   // début du temps de sample, qui convetira tout seul après
    Last_ADC_Convert = ADC_CHAN_VBAT;
}

void ADC_Every_ms(void)
{
    static u16 Maxtime = 0;
    u16 val16;
    if (AD1CON1bits.DONE) {
        AD1CON1bits.DONE = 0;
        val16 = ADC1BUF0;
        if (Last_ADC_Convert == ADC_CHAN_VBAT) {
            V_Vbat = val16 * GAIN_VBAT;
            AD1CHS0bits.CH0SA = ADC_CHAN_5V;
            Last_ADC_Convert = ADC_CHAN_5V;
        } else {    // if (Last_ADC_Convert == ADC_CHAN_5V) {
            V_5V = val16 * GAIN_5V;
            if (V_5V < SEUIL_URGENCE_5V)
                Mode_Urgence = 1;
            AD1CHS0bits.CH0SA = ADC_CHAN_VBAT;
            Last_ADC_Convert = ADC_CHAN_VBAT;
        }
        AD1CON1bits.SAMP = 1;
    } else {
        Maxtime ++;
        if (Maxtime > 20) {
            printf("ADC_Error\n");
            ADC_Init();
            Maxtime = 0;
            //Error_ADC = 1;
        }
    }
}

float Get_V_5V (void)
{   return V_5V;    }

float Get_V_Vbat (void)
{   return V_Vbat;  }
    
void Print_5V_Cmd(void)
{
    printf("%.1f", Get_V_5V());
}

void Print_VBAT_Cmd(void)
{
    printf("%.1f", Get_V_Vbat());
}
