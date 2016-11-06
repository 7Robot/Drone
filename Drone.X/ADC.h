#ifndef __ADC_H
#define __ADC_H


#define ADC_CHAN_VBAT       0       // AN0
#define ADC_CHAN_5V         1       // AN1

#define GAIN_VBAT           ((4.3*3.3)/1024)
#define GAIN_5V             ((2*3.3)/1024)


void ADC_Init(void);
void ADC_Every_ms(void);

float Get_V_5V (void);
float Get_V_Vbat (void);

void Print_5V_Cmd(void);
void Print_VBAT_Cmd(void);

#endif