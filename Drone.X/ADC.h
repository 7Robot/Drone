#ifndef __ADC_H
#define __ADC_H


#define ADC_CHAN_VBAT       0       // AN0
#define ADC_CHAN_5V         1       // AN1

void ADC_Init(void);
u16 ADC_Convert(u8 chan);

#endif