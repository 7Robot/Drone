
#ifndef __RF_TEST_H
#define __RF_TEST_H

// trames lanc�es par le master
// master commence donn�e avec qq caract�res
// le slave r�pond ACK et donn�es
// le master r�pond ACK aussi

// si slave a pas compris, ben NACK, le master r�pete
// si master a pas compris, NACK, le slave r�p�te

// num�ro de la tramme

// donn�es : 0x0A
// ACK  : 0x11
// NACK : 0x80

// trame ACK
// trame NACK

// trammes donn�es :
// num�ro de la trame, nb de data, checksum (sur num�ro, nb, et data)

// 1 octet pour type de donn�e

// etats pour le master :
// repos
// sending
// attente retour slave
// => soit resend (X fois max) et retour attente
// => soit send ACK et retour repos
// => soit send NACK et retour attente

// etats pour slave
// repos (attente message de master)
// => soit NACK et retour repos
// => soit ACK + donn�es et suite
// attente r�ponse master
// => soit ACK et retour repos
// => soit NACK et resend et retour attente


#define RF_COMM_SIZE 200

#define RF_COMM_REPOS   0
#define RF_COMM_SENDING 1
#define RF_COMM_WAIT    2

#define RF_IS_MASTER 1
#define RF_IS_SLAVE  2

u8 RF_Set_Slave_Cmd (void);
u8 RF_Set_Master_Cmd (void);

u8 RF_Read_All_Reg_Cmd (void);
u8 RF_Send_Packet_Cmd(void);
u8 RF_Wait_For_Packet_Cmd(void);



#endif