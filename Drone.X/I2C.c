#include "main.h"


#define Timer_ms1 Compteur_ms_1

#if I2C_MASTER


volatile uint8_t state_i2c = 0;

uint16_t I2C_timer; //stockage du temps
uint8_t I2C_Maxtimed = 0;
uint8_t I2C_Nacked = 0;

uint8_t I2C_i = 0;

I2C_command Liste_I2C_Command[I2C_CMD_LIST_SIZE];
I2C_command Current_I2C_Cmd;

uint8_t cmd_I2C_DONE = 0;
uint8_t cmd_I2C_TODO = 0;



void Init_I2C(void) {
    //setting baud rate:
    uint16_t Fscl = 20000;
    uint16_t BRG = (((1/Fscl))*FCY/2)-2;
    I2C1BRG = BRG;
    
    I2C1CONbits.IPMIEN = 0;
    
    IEC1bits.MI2C1IE = 1; //I2C Master Events interupt enable
    IPC4bits.MI2C1IP = 0b001; //priority 1
    
}

void __attribute__((interrupt,auto_psv)) _MI2C1Interrupt (void) {
    
    IFS1bits.MI2C1IF = 0;
    
    if ((state_i2c == 2) || (state_i2c == 10)) {   // attente de l'envoi du start ou du restart
        if (I2C1STATbits.S == 1) { // in case of start event 
            state_i2c++;
        }
    } else if (state_i2c == 4) {  // phase d'envoi, adresse puis data
        if (!I2C1STATbits.TBF && !I2C1STATbits.TRSTAT) {    // envoi actuel fini
            if (!I2C1STATbits.ACKSTAT) {    // si il y a bien eu ACK du slave
                if (I2C_i < Current_I2C_Cmd.nbr_byte_send) {    // tant qu'on a qqchose à envoyer, on envoie
                    I2C1TRN = Current_I2C_Cmd.data_send[I2C_i];
                    I2C_timer = Timer_ms1;
                    I2C_i ++;
                } else {
                    state_i2c = 9;
                }
            } else {
                state_i2c = 30;
            }
        }
    } else if (state_i2c == 12) {    // on a envoyé l'adresse read
        if (!I2C1STATbits.TBF && !I2C1STATbits.TRSTAT) {    // envoi fini
            if (!I2C1STATbits.ACKSTAT) {    // si il y a bien eu ACK du slave
                state_i2c += 2;
            } else {
                state_i2c = 30;
            }
        }
        
        
    } else if (state_i2c == 15) {
        if (I2C1STATbits.RBF) {
            Current_I2C_Cmd.data_read[I2C_i] = I2C1RCV;
            I2C_i++;
            if (I2C_i < Current_I2C_Cmd.nbr_byte_read) {
                I2C1CONbits.ACKDT = 0; //ack
                I2C1CONbits.ACKEN = 1;
            } else {
                I2C1CONbits.ACKDT = 1; //nack
                I2C1CONbits.ACKEN = 1;
            }
            state_i2c ++;
        }
    } else if (state_i2c == 16) {
        if (!I2C1CONbits.ACKEN) {
            if (I2C_i < Current_I2C_Cmd.nbr_byte_read) {
                I2C1CONbits.RCEN = 1; //allow the master to receive data
                state_i2c --;
            } else {
                state_i2c = 19;
            }
            I2C_timer = Timer_ms1;
        }
    } else if (state_i2c == 20) {
        if (!I2C1CONbits.PEN) {
            state_i2c ++;
        }
    }
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

void Transmit_I2C_Loop(void) {
    switch (state_i2c){
        case 0:
            if(cmd_I2C_TODO != cmd_I2C_DONE) {
                IFS1bits.MI2C1IF = 0;
                I2C1CONbits.I2CEN = 1;
                Current_I2C_Cmd = Liste_I2C_Command[cmd_I2C_DONE];
                state_i2c++;
            }
            break;
            
        case 1: //start event
            I2C1CONbits.SEN = 1; // Initiates the Start condition on the SDAx and SCLx pins
            I2C_timer = Timer_ms1;
            state_i2c++;
            break;
        case 2:
            if ((Timer_ms1 - I2C_timer) > 10){ //max time
                I2C_Maxtimed = 1;
                state_i2c = 30; 
            }
            break;
        case 3: //send device addr
            if (Current_I2C_Cmd.nbr_byte_send != 0) {
                I2C1TRN = (Current_I2C_Cmd.i2c_addr << 1) + 0; // 7bits addr + R/W bit
                I2C_i = 0;
                I2C_timer = Timer_ms1;
                state_i2c++;
            } else {
                state_i2c = 11;
            }
            break;
        case 4:   // la c'est l'IT qui gere tout l'envoi
            if ((Timer_ms1 - I2C_timer) > 10){ //max time
                I2C_Maxtimed = 1;
                state_i2c = 30; 
            }
            break;
            
        
        case 9:
            if (Current_I2C_Cmd.nbr_byte_read != 0) {
                I2C1CONbits.RSEN = 1; // ReStart
                I2C_timer = Timer_ms1;
                state_i2c++;
            } else {
                state_i2c = 19;
            }
            break;
        case 10:
            if ((Timer_ms1 - I2C_timer) > 10) { //max time
                I2C_Maxtimed = 1;
                state_i2c = 30; 
            }
            break;   
        case 11:
            I2C1TRN = (Current_I2C_Cmd.i2c_addr << 1) + 1; // 7bits addr + R/W bit
            I2C_i = 0;
            I2C_timer = Timer_ms1;
            state_i2c ++;
            break;
        case 12: 
            if ((Timer_ms1 - I2C_timer) > 10){ //max time
                I2C_Maxtimed = 1;
                state_i2c = 30; 
            }
            break;
        //////////////////////////READ//////////////////////////////////////////    
        case 14:
            I2C1CONbits.RCEN = 1; //allow the master to receive data
			I2C_timer = Timer_ms1;
            state_i2c ++;
            break;
        
        case 15:    // c'est l'IT qui gere la recepetion
        case 16:    // et l'envoi de l'acknoledge/Nack durant ces etats
            if ((Timer_ms1 - I2C_timer) > 10){ //max time
                I2C_Maxtimed = 1;
                state_i2c = 30; 
            }
            break;
        case 19:
            I2C1CONbits.PEN = 1;
            state_i2c ++;
            I2C_timer = Timer_ms1;
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
            printf("I2C_Maxtimed\n");
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
            printf("Unexpected I2C_State : %d\n", state_i2c);
            state_i2c = 30;		// "faux" fini
            break;
    }
}



uint8_t I2C_Done;
uint8_t I2C_Test_Data[15] = {51,52,53,54};

uint8_t I2C_Wr_Cmd(void){
    uint8_t add;
    uint8_t nb_data;
    
    float valf;
    if (Get_Param_Float(&valf)){
        return 2;
    }
    add = valf;
    if (Get_Param_Float(&valf)){
        return 2;
    }
    nb_data = valf;
    
    int i;
    for (i = 0; i < 15; i ++) {
        I2C_Test_Data[i] = 50 + i;
    }
    
    Add_I2C_command(add, nb_data, 0, &I2C_Test_Data[0], &I2C_Test_Data[0], &I2C_Done);
    return 0;
}

uint8_t I2C_Rd_Cmd(void){
    uint8_t add;
    uint8_t nb_data;
    float valf;
    if (Get_Param_Float(&valf)){
        return 2;
    }
    add = valf;
    if (Get_Param_Float(&valf)){
        return 2;
    }
    nb_data = valf;
    //I2C_Read(add, reg, nb_data, &data[0]);
    I2C_Done = 0;
    int i;
    for (i = 0; i < 15; i ++) {
        I2C_Test_Data[i] = 6;
    }
    Add_I2C_command(add, 0, nb_data, &I2C_Test_Data[0], &I2C_Test_Data[0], &I2C_Done);
    while (!I2C_Done) {
        Transmit_I2C_Loop();
    }
    for (i = 0; i < nb_data; i++){
        printf("%d:%d\n", i, I2C_Test_Data[i]);
    }
    return 0;
}

uint8_t I2C_Wr_Rd_Cmd(void){
    uint8_t add;
    uint8_t nb_data;
    float valf;
    if (Get_Param_Float(&valf)){
        return 2;
    }
    add = valf;
    if (Get_Param_Float(&valf)){
        return 2;
    }
    nb_data = valf;
    //I2C_Read(add, reg, nb_data, &data[0]);
    I2C_Done = 0;
    int i;
    for (i = 0; i < 15; i ++) {
        I2C_Test_Data[i] = 6;
    }
    Add_I2C_command(add, nb_data, nb_data, &I2C_Test_Data[0], &I2C_Test_Data[0], &I2C_Done);
    while (!I2C_Done) {
        Transmit_I2C_Loop();
    }
    for (i = 0; i < nb_data; i++){
        printf("%d:%d\n", i, I2C_Test_Data[i]);
    }
    return 0;
}

uint8_t I2C_Stress_Mode = 0;
uint8_t I2C_Stress_Done = 1;
uint8_t I2C_Stress_Data[10] = {0}; 
uint32_t I2C_Stress_Count = 0;
uint32_t I2C_Stress_Timer = 0;

void I2C_Stress_Loop (void) {
    // mode 0 : repos
    // 10 => 19 : write avec 1 à 10 data
    // 20 => 29 : rd avec 1 à 10 data
    if (I2C_Stress_Mode && I2C_Stress_Done) {
        if ((I2C_Stress_Mode >= 10) && (I2C_Stress_Mode <= 19)) {
            I2C_Stress_Done = 0;
            I2C_Stress_Count += I2C_Stress_Mode - 9;
            Add_I2C_command(0x20, I2C_Stress_Mode - 9, 0, &I2C_Stress_Data[0], NULL, &I2C_Stress_Done);
            
        } else if ((I2C_Stress_Mode >= 20) && (I2C_Stress_Mode <= 29)) {
            I2C_Stress_Done = 0;
            I2C_Stress_Count += I2C_Stress_Mode - 19;
            Add_I2C_command(0x20, 0, I2C_Stress_Mode - 19, NULL, &I2C_Stress_Data[0], &I2C_Stress_Done);
        }
    }
}

uint8_t I2C_Stress_Cmd(void) {
    float valf;
    if (Get_Param_Float(&valf)){
        printf("%ld in %ld\n", I2C_Stress_Count, (Timer_ms1 - I2C_Stress_Timer));
        valf = 0.001 * (Timer_ms1 - I2C_Stress_Timer);
        valf = I2C_Stress_Count / valf;
        printf("%.3f\n", valf);
    } else {
        I2C_Stress_Mode = valf;
        I2C_Stress_Timer = Timer_ms1;
        I2C_Stress_Count = 0;
        if (I2C_Stress_Mode == 50) {
            I2C_Stress_Mode = 0;
            printf("BRG %d\n", I2C1BRG);
            
            uint32_t Fscl = 70000;
            uint32_t BRG = (FCY/(2*Fscl)) - 2;
            printf("BRG Cal %ld\n", BRG);
            
        } else if (I2C_Stress_Mode == 51) {
            I2C_Stress_Mode = 0;
            printf("BRG %d\n", I2C1BRG);
            I2C1BRG = (0.99 * I2C1BRG);
            printf("BRG %d\n", I2C1BRG);
            
        } else if (I2C_Stress_Mode == 52) {
            I2C_Stress_Mode = 0;
            printf("BRG %d\n", I2C1BRG);
            I2C1BRG = (1.01 * I2C1BRG) + 1; 
            printf("BRG %d\n", I2C1BRG);
            
        }
    }
    return 0;
}



#else
uint8_t Data_To_Send = 48; //truc au pif pour le premier test

void Init_I2C(void){
    I2C1CONbits.IPMIEN = 0;
    I2C1CONbits.STREN = 1;  // active la pause d'horloge
    //I2C1CONbits.STREN = 0;
    
    //IEC1bits.SI2C1IE = 1; //I2C Slave Events interupt enable
    //IPC4bits.SI2C1IP = 0b001; //priority 1
    
    I2C1ADD = 0x20; //adresse du slave
    I2C1CONbits.A10M = 0; //adresse sur 7-bits
    
    I2C1CONbits.I2CEN = 1;
    uint8_t poubelle = I2C1RCV; //on vide le buffer de reception au cas ou
    
  
}

uint8_t i2c_state = 0;
uint8_t Old_i2c_state = 0;
uint16_t Last_Timer = 0;

uint8_t Start_Detect = 0;
uint8_t Stop_Detect = 0;

uint32_t Nb_Rx = 0;
uint32_t Nb_Tx = 0;


void Gestion_I2C_Slave_Loop(void){
    uint8_t msg;//sert a vider les buffers

    if (Start_Detect != I2C1STATbits.S) {
        Start_Detect = I2C1STATbits.S;
        if (I2C1STATbits.S) {
            //printf("S %ld %ld\n", Nb_Rx, Nb_Tx);
            i2c_state = 2;
        }
    }
    if (Stop_Detect != I2C1STATbits.P) {
        Stop_Detect = I2C1STATbits.P;
        if (I2C1STATbits.P) {
            //printf("P\n");
            i2c_state = 0;
        }
    }
    
    switch(i2c_state){         
        case 2: //etat de reception
            if(I2CSTATbits.RBF){ //si le buffer de reception est plein
                I2C1CONbits.ACKDT = 0; 
                I2C1CONbits.ACKEN = 1;
                I2C1CONbits.SCLREL = 1; //relache la ligne scl
                if(!I2CSTATbits.D_A){ //si c'était une adresse
                    if (I2CSTATbits.R_W) { // en mode lecture pour le master, on va envoyer
                        i2c_state = 10;
                    } else {
                        // sinon on reste ici pour recevoir
                    }
                    msg = I2C1RCV;//on vide la reception   
                } else { //on est en lecture de data
                    msg = I2C1RCV;
                    //printf("msg: %d\n", msg);
                    Nb_Rx ++;
                }
            }
            break;
            
            
    ///////////////////////// Ecriture ///////////////////////////////////////       
        case 10:
            if (!I2C1CONbits.SCLREL) {
                i2c_state++;
            }
            break;
        case 11:
            IFS1bits.SI2C1IF = 0;
            I2C1TRN = Data_To_Send;
            Nb_Tx ++;
            I2C1CONbits.SCLREL = 1; //relache la ligne scl
            //printf("d%d\n", (int)(Data_To_Send));
            Data_To_Send ++;
            i2c_state++;
            break;
        case 12:
            if(!I2C1STATbits.TBF){
                i2c_state++;
            }
            break;
        case 13: //si le buffer de transmission est vide
            if(IFS1bits.SI2C1IF){
                
            ////// LA JE NE SAIS PAS SI CE REGISTRE EST MODIFIE OU SI JE DOIS JUSTE LIRE L42TAT DE LA LIGNE POUR VOIR SI IL Y A UN ACK OU UN NACK
                
                if(!I2C1STATbits.ACKSTAT){ //ack reçu du master donc on continue d'envoyer
                    i2c_state = 11;
                }else{
                    i2c_state = 0; //nack reçut transmission finit on attend
                    Start_Detect = 0;
                }
            }
            break;            
    ///////////////////////// Lecture ///////////////////////////////////////       
        default:
            i2c_state = 0;
            break;
            
    }
    
    if (i2c_state != Old_i2c_state) {
        Old_i2c_state = i2c_state;
        //printf("%d,", (int)(i2c_state));
        Last_Timer = Timer_ms1;
    }
    
    if ((Timer_ms1 - Last_Timer) > 1000) {
        if (i2c_state != 0) {
            printf("Reset_I2C\n");
            I2C1CONbits.I2CEN = 0;
            Start_Detect = 0;
            Stop_Detect = 0;
            i2c_state = 0;
            I2C1CONbits.I2CEN = 1;
        }
    }
}


uint8_t I2C_Wr_Cmd(void){
    return 0;
}

uint8_t I2C_Rd_Cmd(void){
    printf("i2c_state %d\n", i2c_state);
    printf("Start_Detect %d\n", Start_Detect);
    printf("Stop_Detect %d\n", Stop_Detect);
    return 0;
}
uint8_t I2C_Wr_Rd_Cmd(void){
    return 0;
}
uint8_t I2C_Stress_Cmd(void) {
    return 0;
}

void Init_I2C_int(void){
    I2C1CONbits.IPMIEN = 0;
    I2C1CONbits.STREN = 1;  // active la pause d'horloge
    //I2C1CONbits.STREN = 0;
    
    IEC1bits.SI2C1IE = 1; //I2C Slave Events interupt enable
    IPC4bits.SI2C1IP = 0b001; //priority 1
    
    I2C1ADD = 0x20; //adresse du slave
    I2C1CONbits.A10M = 0; //adresse sur 7-bits
    
    I2C1CONbits.I2CEN = 1;
    uint8_t poubelle = I2C1RCV; //on vide le buffer de reception au cas ou
    
}


uint8_t Read_Write_status = 0;

void __attribute__((interrupt,auto_psv)) _SI2C1Interrupt (void){
    IFS1bits.SI2C1IF = 0;
    if(Start_Detect != I2C1STATbits.S){
        Start_Detect = I2C1STATbits.S;
        i2c_state = 1;
    }else if(Stop_Detect != I2C1STATbits.P){
        Stop_Detect = I2C1STATbits.P;
        i2c_state = 0;
   
    }else if(!I2C1STATbits.D_A){//si la dernière donnée reçut c'est une addresse
        Read_Write_status = I2C1STATbits.R_W;
        i2c_state = 2;
    }else if(I2C1STATbits.D_A){//si la dernière donnée reçut est une data
        i2c_state++;
        
    }else if(i2c_state == 12){
        if(!I2C1STATbits.ACKSTAT){ //ack reçu du master donc on continue d'envoyer
           i2c_state = 10;
        }else if(I2C1STATbits.ACKSTAT){ //ack reçu du master donc on continue d'envoyer
           i2c_state = 0; //nack reçut transmission finit on attend
           Start_Detect = 0;
        }
    }
}

void Gestion_I2C_Slave_int_Loop(void){
    uint8_t msg;
    switch(i2c_state){
        case 0:
            //on ne fait rien dans cet état puisque le slave est en attente d'un start
            break;
        case 1:
            //on ne fait rien ici on attend que l'adresse avec le bit de lecture/ecriture soit recu
            break;
        case 2: 
            I2C1CONbits.ACKDT = 0; 
            I2C1CONbits.ACKEN = 1;
            I2C1CONbits.SCLREL = 1; //relache la ligne scl
            if (Read_Write_status) { // en mode lecture pour le master, on va envoyer
                msg = I2C1RCV;//on vide la reception
                i2c_state = 10;
            } else {
                i2c_state = 20;  
            }  
            break;
            
            
    /////////////////////////mode lecture pour master///////////////////////////        
        case 10:
            I2C1TRN = Data_To_Send;
            I2C1CONbits.SCLREL = 1; //relache la ligne scl
            Data_To_Send ++;
            i2c_state++;
            break;
        case 11:
            //on fait rien on attend l'interruption qui indique que la transmission c'est bien passé
            break;   
            
    /////////////////////////mode ecriture pour master///////////////////////////        
        case 20:
            msg = I2C1RCV;//on vide la reception
            i2c_state++;
            break;
        case 21:
            //on fait rien
            break;
        case 22:
            I2C1CONbits.ACKDT = 0; 
            I2C1CONbits.ACKEN = 1;
            I2C1CONbits.SCLREL = 1; //relache la ligne scl
            i2c_state = 20;
            break;
    }
}

#endif