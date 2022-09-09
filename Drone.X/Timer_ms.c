


#include "main.h"


<<<<<<< HEAD
volatile u16 Timer_ms1 = 0;
=======
volatile u16 Compteur_ms_1 = 0;
>>>>>>> master_test_martin

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
<<<<<<< HEAD
    u16 Delay_Var = Timer_ms1;
    while ((Delay_Var - Timer_ms1) < Delay_Time);
=======
    u16 Start_Time = Compteur_ms_1;
    while ((Compteur_ms_1 - Start_Time) < Delay_Time);
>>>>>>> master_test_martin
}

void __attribute__((interrupt,auto_psv)) _T1Interrupt(void)
{
    static u16 i = 0;
    i++;
    if (i == 900) {
        LED2 = !LED2;
        i = 0;
    }
<<<<<<< HEAD
    
=======
>>>>>>> master_test_martin
    
    Timer_ms1 ++;

    
    IFS0bits.T1IF = 0;  // clear du flag
}