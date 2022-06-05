


#include "main.h"


char Current_Cmd[MAX_CMD_LENGTH+1];
u16 i_Current_Cmd = 0;
u16 i_Lecture_Current_Cmd = 0; 

const Command Command_List[] = {
    
 {  "5V"        ,Print_5V_Cmd},
 {  "VBAT"      ,Print_VBAT_Cmd},
 
// {  "ALLI2C"    ,I2C_Try_All_Cmd},
// {  "ALTI"      ,Alti_Read_Cmd},
 //{  "TACCEL"    ,I2C_Try_Accel_Cmd},
// {  "ACCEL"     ,Accel_Print_Cmd},
 
 
 
 {  "GPSON"     ,GPS_Send_On_Pin_Cmd},
 {  "GPSOFF"    ,GPS_Send_OFF_Pin_Cmd},
 {  "GPSSENDOFF"  ,GPS_Send_Off_Cmd},
 {  "GPSFAST"   ,GPS_Go_Fast_Cmd},
 {  "GPSSLOW"   ,GPS_Go_Slow_Cmd},
 {  "GPSBAUD"   ,GPS_try_baudrates_Cmd},
 
 
 {  "RFRST"     ,RF_Reset_Cmd},
 {  "RFI"       ,RF_Init_Cmd},
 {  "RFREAD"    ,RF_Read_All_Reg_Cmd},
 {  "RFSEND"    ,RF_Send_Packet_Cmd},
 {  "RFWAIT"    ,RF_Wait_For_Packet_Cmd},
 
 {  "RFSLAVE"   ,RF_Set_Slave_Cmd},
 {  "RFMASTER"  ,RF_Set_Master_Cmd},
 
 
 // {  "RFSTATUS"  ,RF_Print_Status_Cmd},
 // {  "RFSPI"     ,Test_Config_SPI_Cmd},
 
 {  "PRINTCMD"  ,Print_All_CMD_Cmd},
 {  "HELP"      ,Print_All_CMD_Cmd},
 
};

const u16 Command_List_Length = sizeof(Command_List) / sizeof(Command_List[0]);

void Interp(char c)
{
    // fin de commande = entrée,
    if (c != '\n') {
        if (i_Current_Cmd < MAX_CMD_LENGTH) { //si on est toujours dans la commande, on ajoute
            Current_Cmd[i_Current_Cmd] = To_UpperCase(c);
            i_Current_Cmd ++;
        } else if (i_Current_Cmd < (MAX_CMD_LENGTH+1)) {   // protection overshoot
            i_Current_Cmd ++;
        }
    } else { // on a tappé entrée, il faut trouver quelle fonction executer..
        if (i_Current_Cmd == (MAX_CMD_LENGTH+1)) {
            printf("Overshoot\r\n");
        } else {

            Current_Cmd[i_Current_Cmd] = '\0';  // mise d'un fin de chaine à la fin
            // on recherche combien de cartères fait la commande en elle même
            u16 Len = 0;
            u16 Ind = 0;
            u16 Found = 0;
            while ((Current_Cmd[Len] >= 'A' && Current_Cmd[Len] <= 'Z') || (Current_Cmd[Len] >= '0' && Current_Cmd[Len] <= '9'))
                Len++;
            if (Len) {
                i_Lecture_Current_Cmd = Len;
                while ((!Found) && (Ind < Command_List_Length)) {
                    if (Comp_Cmd(Len, Ind)) 
                        Found = Ind+1;
                    else
                        Ind ++;
                }
                if (!Found){
                    printf("Cmd Not Found\r\n");
                } else {
                    u8 val8 = (*Command_List[Found-1].Func)();
                    if (val8)
                        printf("Cmd Error : %d\r\n", val8);
                }
            }
        }
        i_Current_Cmd = 0;
    }
}

u8 Comp_Cmd (u16 Len, u16 ind)
{   
    u16 i = 0;
    u16 err = 0;
    
    while (!err && (i < Len)) {
        if (Command_List[ind].Name[i] != Current_Cmd[i])
            err = 1;
        i++;
    }
    // si erreur, c'est que c'est pas bon
    if (err)
        return 0;
    else if (Command_List[ind].Name[Len] != '\0') // mais si on n'est pas non plus au fond du nom, c'est pas bon
        return 0;
    else 
        return 1;
}

char To_UpperCase (char c)
{
    if (c >= 'a' && c <= 'z')
        return c - 32;
    else 
        return c;
}

u8 Get_Param_Float (float *retour)
{
    float valf = 0;
    float div = 0;
    // tant qu'on est sur un caractère, et qu'on a pas trouvé un chiffre
    while ( (Current_Cmd[i_Lecture_Current_Cmd] != '\0') && 
            !( (Current_Cmd[i_Lecture_Current_Cmd] >= '0') && (Current_Cmd[i_Lecture_Current_Cmd] <= '9')) )
        i_Lecture_Current_Cmd ++;
    
    if (Current_Cmd[i_Lecture_Current_Cmd] == '\0') // si on est au bout, on renvoie error...
        return 1;
    
    while ( ( (Current_Cmd[i_Lecture_Current_Cmd] >= '0') && (Current_Cmd[i_Lecture_Current_Cmd] <= '9') ) || (Current_Cmd[i_Lecture_Current_Cmd] == '.') ) {
        if (Current_Cmd[i_Lecture_Current_Cmd] != '.') {
            valf *= 10;
            valf += Current_Cmd[i_Lecture_Current_Cmd] - '0';
            div *= 10;
        } else {
            div = 1;
        }
        i_Lecture_Current_Cmd ++;
    }
    if (div == 0)
        div = 1;
    
    *retour = valf/div;

    return 0;
}

u8 Print_All_CMD_Cmd (void)
{
    u16 i;
    for (i = 0; i < Command_List_Length; i++) {
        printf("%s\n", Command_List[i].Name);
        Wait_Transmited();
    }
    return 0;
}