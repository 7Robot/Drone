#ifndef __TIMER_MS_H
#define __TIMER_MS_H


void Timer_Ms_Init(void);

void Delay_ms (u32 Delay_Time);
void Set_Maxtime (u32 Val_Maxtime);
u8 Get_Maxtime(void);


//extern volatile u32 Maxtime;
extern volatile u32 Compteur_ms_1;
#endif