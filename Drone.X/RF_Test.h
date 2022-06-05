
#ifndef __RF_TEST_H
#define __RF_TEST_H

// trames lancées par le master
// master commence donnée avec qq caractères
// le slave répond ACK et données
// le master répond ACK aussi

// si slave a pas compris, ben NACK, le master répete
// si master a pas compris, NACK, le slave répéte

// numéro de la tramme

// données : 0x0A
// ACK  : 0x11
// NACK : 0x80

// trame ACK
// trame NACK

// trammes données :
// numéro de la trame, nb de data, checksum (sur numéro, nb, et data)

// 1 octet pour type de donnée

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
// => soit ACK + données et suite
// attente réponse master
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