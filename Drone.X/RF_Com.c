


#include "main.h"


/*
void RF_Add_FIFO_TX(u8 Data);
u8 RF_Still_Transmitting (void);
u8 RF_In_Error (void);
void RF_FIFO_TX_Send (void);
u8 RF_Get_FIFO_RX (void);
u8 RF_Get_Nb_Data_FIFO_RX (void);
void RF_Set_RX_Mode(void);

*/

// 0 : Slave, 1 = Master
u8 RF_Mode = 0;
// 0 : Iddle
// 1 : RX (default)


// sequence
// comme stage daniel
// soit trame de data, le slave répond par ACK (ou NACK, le master renvoit)
// soit demande de data, le slave répond par data, le master par ACK
// Message : quoi (Data / request / ACK / NACK)
//  				si  Data, Num Message, Nb Data, [Datas ...], CheckSum

u8 RF_State = 0;