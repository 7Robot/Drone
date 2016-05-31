


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

void Set_Maxtime (u32 Val_Maxtime)
{   Maxtime = Val_Maxtime;  }

u8 Get_Maxtime(void)
{   
    if (Maxtime != 0)
        return 1;
    else 
        return 0;
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

    ADC_Every_ms();
    
    IFS0bits.T1IF = 0;  // clear du flag
}