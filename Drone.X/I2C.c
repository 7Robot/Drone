#include "main.h"


#if I2C_MASTER

volatile uint8_t state_i2c = 0;

uint32_t I2C_timer; //stockage du temps
uint8_t I2C_Maxtimed = 0;

uint8_t I2C_i = 0;

I2C_command Liste_I2C_Command[I2C_CMD_LIST_SIZE];
I2C_command Current_I2C_Cmd;

uint8_t cmd_I2C_DONE = 0;
uint8_t cmd_I2C_TODO = 0;

void Init_I2C(void){
    //setting baud rate:
    uint16_t Fscl = 20000;
    uint16_t BRG = (((1/Fscl))*FCY/2)-2;
    I2C1BRG = BRG;
    
    I2C1CONbits.IPMIEN = 0;
    
    IEC1bits.MI2C1IE = 1; //I2C Master Events interupt enable
    IPC4bits.MI2C1IP = 0b001; //priority 1
    
    //I2C1CONbits.I2CEN = 1; //enable I2C
}

void __attribute__((interrupt,auto_psv)) _MI2C1Interrupt (void){
    IFS1bits.MI2C1IF = 0;
    state_i2c ++;
}

void Add_I2C_command(uint8_t i2c_addr, uint8_t nbr_byte_send, uint8_t nbr_byte_read, uint8_t data_send[], uint8_t data_read[], void *Done){
    Liste_I2C_Command[cmd_I2C_TODO].nbr_byte_send = nbr_byte_send;
    Liste_I2C_Command[cmd_I2C_TODO].nbr_byte_read = nbr_byte_read;
    Liste_I2C_Command[cmd_I2C_TODO].data_read = data_read;
    Liste_I2C_Command[cmd_I2C_TODO].data_send = data_send;
    Liste_I2C_Command[cmd_I2C_TODO].i2c_addr = i2c_addr;
    Liste_I2C_Command[cmd_I2C_TODO].Done = Done;
    cmd_I2C_TODO++;
    if(cmd_I2C_TODO == I2C_CMD_LIST_SIZE)
        cmd_I2C_TODO = 0;
}

void Transmit_I2C_Loop(void){
    switch (state_i2c){
        case 0:
            if(cmd_I2C_TODO != cmd_I2C_DONE){
                IFS1bits.MI2C1IF = 0;
                I2C1CONbits.I2CEN = 1;
                Current_I2C_Cmd = Liste_I2C_Command[cmd_I2C_DONE];
                state_i2c++;
            }
            break;
            
        case 1: //start event
            I2C1CONbits.SEN = 1; // Initiates the Start condition on the SDAx and SCLx pins
            I2C_i=0;
            I2C_timer = Timer_ms1;
            state_i2c++;
            break;
        case 2://if (!I2C1CONbits.SEN)
            if ((Timer_ms1 - I2C_timer) > 10){ //max time
                I2C_Maxtimed = 1;
                state_i2c = 30; 
            }
            break;
        case 3: //send device addr
            if (Current_I2C_Cmd.nbr_byte_send != 0){
                I2C1TRN = (Current_I2C_Cmd.i2c_addr << 1) + 0; // 7bits addr + R/W bit
                I2C_timer = Timer_ms1;
                state_i2c++;
            }else{
                state_i2c = 11;
            }
            break;
        case 4:
            if ((Timer_ms1 - I2C_timer) > 10){ //max time
                I2C_Maxtimed = 1;
                state_i2c = 30; 
            }
            break;
        case 5: //acknoledge status bit 
            if (I2C1STATbits.ACKSTAT == 0) {
                state_i2c++;
            }else{
                state_i2c = 30;
            }
            break;     
        /////////////////////////////SEND///////////////////////////////////////    
        case 6:
            I2C1TRN = Current_I2C_Cmd.data_send[I2C_i];
            I2C_timer = Timer_ms1;
            I2C_i++;
            state_i2c++;
            break;
        case 7:
            if ((Timer_ms1 - I2C_timer) > 10){ //max time
                I2C_Maxtimed = 1;
                state_i2c = 30; 
            }
            break;
        case 8:
            if (I2C1STATbits.ACKSTAT == 0) {
                if(I2C_i == Current_I2C_Cmd.nbr_byte_send){
                    state_i2c++;
                }else{
                    state_i2c = 6;
                }
            } else{
                state_i2c = 30;
            }
            break;  
        case 9:
            if (Current_I2C_Cmd.nbr_byte_read != 0){
                I2C_i=0;
                I2C1CONbits.RSEN = 1; // ReStart
                I2C_timer = Timer_ms1;
                state_i2c++;
            }else{
                state_i2c = 19;
            }
            break;
        case 10://if (!I2C1CONbits.RSEN)
            if ((Timer_ms1 - I2C_timer) > 10){ //max time
                I2C_Maxtimed = 1;
                state_i2c = 30; 
            }
            break;   
        case 11:
            I2C1TRN = (Current_I2C_Cmd.i2c_addr << 1) + 1; // 7bits addr + R/W bit
            I2C_timer = Timer_ms1;
            state_i2c++;
            break;
        case 12: 
            if ((Timer_ms1 - I2C_timer) > 10){ //max time
                I2C_Maxtimed = 1;
                state_i2c = 30; 
            }
            break;
        case 13:
            if (I2C1STATbits.ACKSTAT == 0) {
                state_i2c++;
            }else{
                state_i2c = 30;
            }
            break;     
        //////////////////////////READ//////////////////////////////////////////    
        case 14:
            I2C1CONbits.RCEN = 1; //allow the master to receive data 
            I2C_timer = Timer_ms1;
            state_i2c++;
            break;
        case 15://if (I2C1STAT.RBF == 1)
            if ((Timer_ms1 - I2C_timer) > 10){ //max time
                I2C_Maxtimed = 1;
                state_i2c = 30; 
            }
            break;
        case 16:
            Current_I2C_Cmd.data_read[I2C_i] = I2C1RCV;
            I2C_i++;
            if(I2C_i == Current_I2C_Cmd.nbr_byte_read){
                I2C1CONbits.ACKDT = 1; //nack
                I2C1CONbits.ACKEN = 1;
            }else{
                I2C1CONbits.ACKDT = 0; //ack
                I2C1CONbits.ACKEN = 1; 
            }
            I2C_timer = Timer_ms1; 
            state_i2c++;
            break;
        case 17: //if (I2C1CONbits.ACKEN == 0) {
            if ((Timer_ms1 - I2C_timer) > 10){ //max time
                I2C_Maxtimed = 1;
                state_i2c = 30; 
            }
            break;
        case 18:
            if(I2C_i == Current_I2C_Cmd.nbr_byte_read){
                state_i2c++;
            }else{
                state_i2c = 14;
            }
            break;
        case 19:
            I2C1CONbits.PEN = 1;
            I2C_timer = Timer_ms1;
            state_i2c++;
            break;
        case 20:
            if ((Timer_ms1 - I2C_timer) > 10){ //max time
                I2C_Maxtimed = 1;
                state_i2c = 30; 
            }
            break;
        case 21: // if (I2C1CONbits.PEN == 0)
            state_i2c = 30;
            break;
        case 30:
            // previent qu'on a fini :
            *((uint8_t*)Current_I2C_Cmd.Done) = 1;
            cmd_I2C_DONE++;
            if (cmd_I2C_DONE >= I2C_CMD_LIST_SIZE){
                cmd_I2C_DONE = 0;  
            }
            I2C1CONbits.I2CEN = 0;
            if (I2C_Maxtimed) {
                I2C_Maxtimed = 0;
                state_i2c = 31;
            } else {
                state_i2c = 0;
            }
            break;
        case 31:
            I2C_timer = Timer_ms1;
            I2C_SCL_PIN = 0;
            I2C_SCL_TRIS = 0;   // fabrique un coup d'horloge sur l'I2C
            state_i2c ++;
            break;
        case 32:
            if ((Timer_ms1 - I2C_timer) > 1) {
                I2C_SCL_PIN = 1;
                I2C_SCL_TRIS = 1;   // relache l'I2C
                state_i2c = 0;
            }
            break;
        default:
            break;
    }
}

#else
uint8_t Data_To_Send = 48; //truc au pif pour le premier test

void Init_I2C(void){
    I2C1CONbits.IPMIEN = 0;
    
    //IEC1bits.SI2C1IE = 1; //I2C Slave Events interupt enable
    //IPC4bits.SI2C1IP = 0b001; //priority 1
    
    I2C1ADD = 0x20; //adresse du slave
    I2C1CONbits.A10M = 0; //adresse sur 7-bits
  
}

uint8_t i2c_state = 0;

void Gestion_I2C_Slave_Loop(void){
    uint8_t poubelle;//sert a vider les buffers
    uint8_t Old_i2c_state = i2c_state;
    switch(i2c_state){
        case 0:
            I2C1CONbits.I2CEN = 1;
            poubelle = I2C1RCV; //on vide le buffer de reception au cas ou
            i2c_state++;
            break;
        case 1:
            if(I2C1STATbits.S){ //detection d'un bit de start/restart
               i2c_state++; 
               //IFS1bits.SI2C1IF = 0;
            }
            break;            
        case 2://etat de verification de l'adresse
            if(I2CSTATbits.RBF){ //si le buffer de reception est plein
                if(!I2CSTATbits.D_A){ //si l'adresse est bonne
                    i2c_state++;
                    poubelle = I2C1RCV;//on vide la reception   
                }else{ //on est en lecture de data
                    poubelle = I2C1RCV;
                    printf("msg: %d", poubelle);
                    i2c_state = 20;
                }         
            } else if (I2C1STATbits.P) {
                i2c_state --;
            }
            break;
            
        case 3: 
            I2C1CONbits.ACKDT=0; 
            if(I2CSTATbits.R_W){ //on passe en mode ecriture
                i2c_state = 10;
            }else{ //sinon on passe en mode lecture
                i2c_state = 20;
            }
            break;          
            
            
    ///////////////////////// Ecriture ///////////////////////////////////////       
        case 10:
            I2C1CONbits.SCLREL = 1; //relache la ligne scl
            i2c_state++;
            break;
        case 11:
            I2C1TRN = Data_To_Send;
            i2c_state++;
            break;
        case 12: //si le buffer de transmission est vide
            if(!I2C1STATbits.TBF){
                
            ////// LA JE NE SAIS PAS SI CE REGISTRE EST MODIFIE OU SI JE DOIS JUSTE LIRE L42TAT DE LA LIGNE POUR VOIR SI IL Y A UN ACK OU UN NACK
                
                if(I2C1STATbits.ACKSTAT){ //ack reçu du master donc on continue d'envoyer
                    i2c_state = 10;
                }else{
                    i2c_state = 1; //nack reçut transmission finit on attend
                }
            }
            break;            
    ///////////////////////// Lecture ///////////////////////////////////////       
        case 20:
            if(I2C1STATbits.P && !I2C1STATbits.S){ //bit de stop
                i2c_state = 1;
            }else{
                i2c_state = 2;
            }
            break;
            
    }
    
    if (i2c_state != Old_i2c_state) {
        printf("I2C => %d\n", i2c_state);
    }
}
#endif