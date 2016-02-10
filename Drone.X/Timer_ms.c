


#include "main.h"

volatile u32 Maxtime = 0;
volatile u32 Delay_Var = 0;
volatile u32 Compteur_ms_1 = 0;

void Timer_Ms_Init(void)
{
    PR1 = FCY/1000;             // 1/1000 de sec
    T1CONbits.TON = 1;
    IFS0bits.T1IF = 0;
    IPC0bits.T1IP = 7;
    IEC0bits.T1IE = 1;          // active l'IT
    
}


void Delay_ms (u32 Delay_Time)
{
    Delay_Var = Delay_Time;
    while (Delay_Var);
}

void __attribute__((interrupt,auto_psv)) _T1Interrupt(void)
{
    static u16 i = 0;
    i++;
    if (i == 500) {
        LED2 = !LED2;
        i = 0;
    }
    if (Maxtime)
        Maxtime--;
    
    if (Delay_Var)
        Delay_Var--;
    
    Compteur_ms_1 ++;
    
    if (ADC_Convert(ADC_CHAN_5V) < 640) {       // 620 = 4V 
        Mode_Urgence = 1;
    }
    IFS0bits.T1IF = 0;  // clear du flag
}