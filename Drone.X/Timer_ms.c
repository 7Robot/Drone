


#include "main.h"


volatile u16 Timer_ms1 = 0;

void Timer_Ms_Init(void)
{
    PR1 = FCY/1000;             // 1/1000 de sec
    T1CONbits.TON = 1;
    IFS0bits.T1IF = 0;
    IPC0bits.T1IP = 7;          // super haute priorité pour le timer général
    IEC0bits.T1IE = 1;          // active l'IT
}

void Delay_ms (u16 Delay_Time)
{
    u16 Delay_Var = Timer_ms1;
    while ((Delay_Var - Timer_ms1) < Delay_Time);
}

void __attribute__((interrupt,auto_psv)) _T1Interrupt(void)
{
    static u16 i = 0;
    i++;
    if (i == 900) {
        LED2 = !LED2;
        i = 0;
    }
    
    
    Timer_ms1 ++;

    
    IFS0bits.T1IF = 0;  // clear du flag
}