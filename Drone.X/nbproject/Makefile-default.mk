#
# Generated Makefile - do not edit!
#
# Edit the Makefile in the project folder instead (../Makefile). Each target
# has a -pre and a -post target defined where you can add customized code.
#
# This makefile implements configuration specific macros and targets.


# Include project Makefile
ifeq "${IGNORE_LOCAL}" "TRUE"
# do not include local makefile. User is passing all local related variables already
else
include Makefile
# Include makefile containing local settings
ifeq "$(wildcard nbproject/Makefile-local-default.mk)" "nbproject/Makefile-local-default.mk"
include nbproject/Makefile-local-default.mk
endif
endif

# Environment
MKDIR=gnumkdir -p
RM=rm -f 
MV=mv 
CP=cp 

# Macros
CND_CONF=default
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
IMAGE_TYPE=debug
OUTPUT_SUFFIX=elf
DEBUGGABLE_SUFFIX=elf
FINAL_IMAGE=dist/${CND_CONF}/${IMAGE_TYPE}/Drone.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}
else
IMAGE_TYPE=production
OUTPUT_SUFFIX=hex
DEBUGGABLE_SUFFIX=elf
FINAL_IMAGE=dist/${CND_CONF}/${IMAGE_TYPE}/Drone.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}
endif

ifeq ($(COMPARE_BUILD), true)
COMPARISON_BUILD=-mafrlcsj
else
COMPARISON_BUILD=
endif

ifdef SUB_IMAGE_ADDRESS
SUB_IMAGE_ADDRESS_COMMAND=--image-address $(SUB_IMAGE_ADDRESS)
else
SUB_IMAGE_ADDRESS_COMMAND=
endif

# Object Directory
OBJECTDIR=build/${CND_CONF}/${IMAGE_TYPE}

# Distribution Directory
DISTDIR=dist/${CND_CONF}/${IMAGE_TYPE}

# Source Files Quoted if spaced
SOURCEFILES_QUOTED_IF_SPACED=main.c Config_bits.c interrupts.c traps.c Timer_ms.c Init_Clk.c UART_PC.c ADC.c I2C.c GPS.c SPI.c Interpreteur.c RF.c RF_Calib.c RF_Test.c I2C_Accel.c I2C_Alti.c

# Object Files Quoted if spaced
OBJECTFILES_QUOTED_IF_SPACED=${OBJECTDIR}/main.o ${OBJECTDIR}/Config_bits.o ${OBJECTDIR}/interrupts.o ${OBJECTDIR}/traps.o ${OBJECTDIR}/Timer_ms.o ${OBJECTDIR}/Init_Clk.o ${OBJECTDIR}/UART_PC.o ${OBJECTDIR}/ADC.o ${OBJECTDIR}/I2C.o ${OBJECTDIR}/GPS.o ${OBJECTDIR}/SPI.o ${OBJECTDIR}/Interpreteur.o ${OBJECTDIR}/RF.o ${OBJECTDIR}/RF_Calib.o ${OBJECTDIR}/RF_Test.o ${OBJECTDIR}/I2C_Accel.o ${OBJECTDIR}/I2C_Alti.o
POSSIBLE_DEPFILES=${OBJECTDIR}/main.o.d ${OBJECTDIR}/Config_bits.o.d ${OBJECTDIR}/interrupts.o.d ${OBJECTDIR}/traps.o.d ${OBJECTDIR}/Timer_ms.o.d ${OBJECTDIR}/Init_Clk.o.d ${OBJECTDIR}/UART_PC.o.d ${OBJECTDIR}/ADC.o.d ${OBJECTDIR}/I2C.o.d ${OBJECTDIR}/GPS.o.d ${OBJECTDIR}/SPI.o.d ${OBJECTDIR}/Interpreteur.o.d ${OBJECTDIR}/RF.o.d ${OBJECTDIR}/RF_Calib.o.d ${OBJECTDIR}/RF_Test.o.d ${OBJECTDIR}/I2C_Accel.o.d ${OBJECTDIR}/I2C_Alti.o.d

# Object Files
OBJECTFILES=${OBJECTDIR}/main.o ${OBJECTDIR}/Config_bits.o ${OBJECTDIR}/interrupts.o ${OBJECTDIR}/traps.o ${OBJECTDIR}/Timer_ms.o ${OBJECTDIR}/Init_Clk.o ${OBJECTDIR}/UART_PC.o ${OBJECTDIR}/ADC.o ${OBJECTDIR}/I2C.o ${OBJECTDIR}/GPS.o ${OBJECTDIR}/SPI.o ${OBJECTDIR}/Interpreteur.o ${OBJECTDIR}/RF.o ${OBJECTDIR}/RF_Calib.o ${OBJECTDIR}/RF_Test.o ${OBJECTDIR}/I2C_Accel.o ${OBJECTDIR}/I2C_Alti.o

# Source Files
SOURCEFILES=main.c Config_bits.c interrupts.c traps.c Timer_ms.c Init_Clk.c UART_PC.c ADC.c I2C.c GPS.c SPI.c Interpreteur.c RF.c RF_Calib.c RF_Test.c I2C_Accel.c I2C_Alti.c



CFLAGS=
ASFLAGS=
LDLIBSOPTIONS=

############# Tool locations ##########################################
# If you copy a project from one host to another, the path where the  #
# compiler is installed may be different.                             #
# If you open this project with MPLAB X in the new host, this         #
# makefile will be regenerated and the paths will be corrected.       #
#######################################################################
# fixDeps replaces a bunch of sed/cat/printf statements that slow down the build
FIXDEPS=fixDeps

.build-conf:  ${BUILD_SUBPROJECTS}
ifneq ($(INFORMATION_MESSAGE), )
	@echo $(INFORMATION_MESSAGE)
endif
	${MAKE}  -f nbproject/Makefile-default.mk dist/${CND_CONF}/${IMAGE_TYPE}/Drone.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}

MP_PROCESSOR_OPTION=33FJ64MC804
MP_LINKER_FILE_OPTION=,--script=p33FJ64MC804.gld
# ------------------------------------------------------------------------------------
# Rules for buildStep: compile
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
${OBJECTDIR}/main.o: main.c  .generated_files/flags/default/54c9188124c11efea49ec7d7a4add6ef8d98da0a .generated_files/flags/default/a733305486dba52bf1b2f0129eacaac696315869
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/main.o.d 
	@${RM} ${OBJECTDIR}/main.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  main.c  -o ${OBJECTDIR}/main.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/main.o.d"      -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1    -omf=elf -DXPRJ_default=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -O0 -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
${OBJECTDIR}/Config_bits.o: Config_bits.c  .generated_files/flags/default/d267b8c0052d7ae0f07eb508f04f802b0b42f4c3 .generated_files/flags/default/a733305486dba52bf1b2f0129eacaac696315869
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/Config_bits.o.d 
	@${RM} ${OBJECTDIR}/Config_bits.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  Config_bits.c  -o ${OBJECTDIR}/Config_bits.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/Config_bits.o.d"      -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1    -omf=elf -DXPRJ_default=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -O0 -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
${OBJECTDIR}/interrupts.o: interrupts.c  .generated_files/flags/default/a0ca74e6d1b80662d6f5ccac1467c65165527286 .generated_files/flags/default/a733305486dba52bf1b2f0129eacaac696315869
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/interrupts.o.d 
	@${RM} ${OBJECTDIR}/interrupts.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  interrupts.c  -o ${OBJECTDIR}/interrupts.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/interrupts.o.d"      -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1    -omf=elf -DXPRJ_default=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -O0 -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
${OBJECTDIR}/traps.o: traps.c  .generated_files/flags/default/5fe607e71e200ae7d99e15b4c6e8741851239a38 .generated_files/flags/default/a733305486dba52bf1b2f0129eacaac696315869
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/traps.o.d 
	@${RM} ${OBJECTDIR}/traps.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  traps.c  -o ${OBJECTDIR}/traps.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/traps.o.d"      -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1    -omf=elf -DXPRJ_default=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -O0 -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
${OBJECTDIR}/Timer_ms.o: Timer_ms.c  .generated_files/flags/default/b0e80040846848530109e3e7b9dcff649aa83ed9 .generated_files/flags/default/a733305486dba52bf1b2f0129eacaac696315869
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/Timer_ms.o.d 
	@${RM} ${OBJECTDIR}/Timer_ms.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  Timer_ms.c  -o ${OBJECTDIR}/Timer_ms.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/Timer_ms.o.d"      -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1    -omf=elf -DXPRJ_default=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -O0 -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
${OBJECTDIR}/Init_Clk.o: Init_Clk.c  .generated_files/flags/default/9302bf160252eea533d21a7423f9e2001ecdd50a .generated_files/flags/default/a733305486dba52bf1b2f0129eacaac696315869
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/Init_Clk.o.d 
	@${RM} ${OBJECTDIR}/Init_Clk.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  Init_Clk.c  -o ${OBJECTDIR}/Init_Clk.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/Init_Clk.o.d"      -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1    -omf=elf -DXPRJ_default=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -O0 -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
${OBJECTDIR}/UART_PC.o: UART_PC.c  .generated_files/flags/default/406f060788686963439aeb68655ba8f009b0bd64 .generated_files/flags/default/a733305486dba52bf1b2f0129eacaac696315869
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/UART_PC.o.d 
	@${RM} ${OBJECTDIR}/UART_PC.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  UART_PC.c  -o ${OBJECTDIR}/UART_PC.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/UART_PC.o.d"      -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1    -omf=elf -DXPRJ_default=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -O0 -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
${OBJECTDIR}/ADC.o: ADC.c  .generated_files/flags/default/41e9c44b3ae0383fc3ba61cca1bf165015d9d640 .generated_files/flags/default/a733305486dba52bf1b2f0129eacaac696315869
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/ADC.o.d 
	@${RM} ${OBJECTDIR}/ADC.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  ADC.c  -o ${OBJECTDIR}/ADC.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/ADC.o.d"      -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1    -omf=elf -DXPRJ_default=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -O0 -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
${OBJECTDIR}/I2C.o: I2C.c  .generated_files/flags/default/30f3073efa393f71f9a0123e8a6fc018d20b98e4 .generated_files/flags/default/a733305486dba52bf1b2f0129eacaac696315869
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/I2C.o.d 
	@${RM} ${OBJECTDIR}/I2C.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  I2C.c  -o ${OBJECTDIR}/I2C.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/I2C.o.d"      -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1    -omf=elf -DXPRJ_default=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -O0 -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
${OBJECTDIR}/GPS.o: GPS.c  .generated_files/flags/default/28bc9a47a43e70a78efd69d7d133e6ae99d0906d .generated_files/flags/default/a733305486dba52bf1b2f0129eacaac696315869
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/GPS.o.d 
	@${RM} ${OBJECTDIR}/GPS.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  GPS.c  -o ${OBJECTDIR}/GPS.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/GPS.o.d"      -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1    -omf=elf -DXPRJ_default=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -O0 -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
${OBJECTDIR}/SPI.o: SPI.c  .generated_files/flags/default/e4d6e33ce01455fb500607cd7a4a88674aa09994 .generated_files/flags/default/a733305486dba52bf1b2f0129eacaac696315869
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/SPI.o.d 
	@${RM} ${OBJECTDIR}/SPI.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  SPI.c  -o ${OBJECTDIR}/SPI.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/SPI.o.d"      -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1    -omf=elf -DXPRJ_default=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -O0 -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
${OBJECTDIR}/Interpreteur.o: Interpreteur.c  .generated_files/flags/default/3fdf6354fa9eb8aed0e151cd2eb2e4853e09c256 .generated_files/flags/default/a733305486dba52bf1b2f0129eacaac696315869
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/Interpreteur.o.d 
	@${RM} ${OBJECTDIR}/Interpreteur.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  Interpreteur.c  -o ${OBJECTDIR}/Interpreteur.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/Interpreteur.o.d"      -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1    -omf=elf -DXPRJ_default=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -O0 -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
${OBJECTDIR}/RF.o: RF.c  .generated_files/flags/default/7eb46b4b079e3acc8ed32645ffcdadbc61a73c33 .generated_files/flags/default/a733305486dba52bf1b2f0129eacaac696315869
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/RF.o.d 
	@${RM} ${OBJECTDIR}/RF.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  RF.c  -o ${OBJECTDIR}/RF.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/RF.o.d"      -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1    -omf=elf -DXPRJ_default=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -O0 -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
${OBJECTDIR}/RF_Calib.o: RF_Calib.c  .generated_files/flags/default/bcd0675ad78f74e4367ebf010658c425675bc983 .generated_files/flags/default/a733305486dba52bf1b2f0129eacaac696315869
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/RF_Calib.o.d 
	@${RM} ${OBJECTDIR}/RF_Calib.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  RF_Calib.c  -o ${OBJECTDIR}/RF_Calib.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/RF_Calib.o.d"      -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1    -omf=elf -DXPRJ_default=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -O0 -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
${OBJECTDIR}/RF_Test.o: RF_Test.c  .generated_files/flags/default/3d8403b1e14e28015beca5431c7e754eb1eec453 .generated_files/flags/default/a733305486dba52bf1b2f0129eacaac696315869
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/RF_Test.o.d 
	@${RM} ${OBJECTDIR}/RF_Test.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  RF_Test.c  -o ${OBJECTDIR}/RF_Test.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/RF_Test.o.d"      -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1    -omf=elf -DXPRJ_default=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -O0 -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
${OBJECTDIR}/I2C_Accel.o: I2C_Accel.c  .generated_files/flags/default/d5b75fc4da04f5166a434f86a1714d005865e0f8 .generated_files/flags/default/a733305486dba52bf1b2f0129eacaac696315869
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/I2C_Accel.o.d 
	@${RM} ${OBJECTDIR}/I2C_Accel.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  I2C_Accel.c  -o ${OBJECTDIR}/I2C_Accel.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/I2C_Accel.o.d"      -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1    -omf=elf -DXPRJ_default=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -O0 -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
${OBJECTDIR}/I2C_Alti.o: I2C_Alti.c  .generated_files/flags/default/4dde8af1d29f7e917ccf9be40e1ee1037cba40b3 .generated_files/flags/default/a733305486dba52bf1b2f0129eacaac696315869
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/I2C_Alti.o.d 
	@${RM} ${OBJECTDIR}/I2C_Alti.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  I2C_Alti.c  -o ${OBJECTDIR}/I2C_Alti.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/I2C_Alti.o.d"      -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1    -omf=elf -DXPRJ_default=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -O0 -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
else
${OBJECTDIR}/main.o: main.c  .generated_files/flags/default/bbd6f8f1291ea02b030768a6b90c80a59b61ab63 .generated_files/flags/default/a733305486dba52bf1b2f0129eacaac696315869
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/main.o.d 
	@${RM} ${OBJECTDIR}/main.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  main.c  -o ${OBJECTDIR}/main.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/main.o.d"        -g -omf=elf -DXPRJ_default=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -O0 -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
${OBJECTDIR}/Config_bits.o: Config_bits.c  .generated_files/flags/default/b82d60bfcf28b64cdca2931882404fce48be02c8 .generated_files/flags/default/a733305486dba52bf1b2f0129eacaac696315869
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/Config_bits.o.d 
	@${RM} ${OBJECTDIR}/Config_bits.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  Config_bits.c  -o ${OBJECTDIR}/Config_bits.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/Config_bits.o.d"        -g -omf=elf -DXPRJ_default=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -O0 -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
${OBJECTDIR}/interrupts.o: interrupts.c  .generated_files/flags/default/8eacfafc9cab957209629e2aec3e00e22320fa08 .generated_files/flags/default/a733305486dba52bf1b2f0129eacaac696315869
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/interrupts.o.d 
	@${RM} ${OBJECTDIR}/interrupts.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  interrupts.c  -o ${OBJECTDIR}/interrupts.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/interrupts.o.d"        -g -omf=elf -DXPRJ_default=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -O0 -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
${OBJECTDIR}/traps.o: traps.c  .generated_files/flags/default/e84b4a8b7607f17a63ed87a4a3d4c30508fd10ab .generated_files/flags/default/a733305486dba52bf1b2f0129eacaac696315869
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/traps.o.d 
	@${RM} ${OBJECTDIR}/traps.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  traps.c  -o ${OBJECTDIR}/traps.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/traps.o.d"        -g -omf=elf -DXPRJ_default=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -O0 -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
${OBJECTDIR}/Timer_ms.o: Timer_ms.c  .generated_files/flags/default/4bf8e240bac84aaea221b1125fa37a24116fc61c .generated_files/flags/default/a733305486dba52bf1b2f0129eacaac696315869
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/Timer_ms.o.d 
	@${RM} ${OBJECTDIR}/Timer_ms.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  Timer_ms.c  -o ${OBJECTDIR}/Timer_ms.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/Timer_ms.o.d"        -g -omf=elf -DXPRJ_default=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -O0 -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
${OBJECTDIR}/Init_Clk.o: Init_Clk.c  .generated_files/flags/default/8d42e9b6f4b97bfd964e21c06374dfeb8a9f5aa2 .generated_files/flags/default/a733305486dba52bf1b2f0129eacaac696315869
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/Init_Clk.o.d 
	@${RM} ${OBJECTDIR}/Init_Clk.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  Init_Clk.c  -o ${OBJECTDIR}/Init_Clk.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/Init_Clk.o.d"        -g -omf=elf -DXPRJ_default=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -O0 -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
${OBJECTDIR}/UART_PC.o: UART_PC.c  .generated_files/flags/default/c6f0c2cc38ed75c655c788b2d1e8909297b659aa .generated_files/flags/default/a733305486dba52bf1b2f0129eacaac696315869
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/UART_PC.o.d 
	@${RM} ${OBJECTDIR}/UART_PC.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  UART_PC.c  -o ${OBJECTDIR}/UART_PC.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/UART_PC.o.d"        -g -omf=elf -DXPRJ_default=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -O0 -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
${OBJECTDIR}/ADC.o: ADC.c  .generated_files/flags/default/76051fd3f9d0ef65bc3438e658b83da8e28e8943 .generated_files/flags/default/a733305486dba52bf1b2f0129eacaac696315869
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/ADC.o.d 
	@${RM} ${OBJECTDIR}/ADC.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  ADC.c  -o ${OBJECTDIR}/ADC.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/ADC.o.d"        -g -omf=elf -DXPRJ_default=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -O0 -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
${OBJECTDIR}/I2C.o: I2C.c  .generated_files/flags/default/53b8bae21c5f98f5e9841358e85b3e44d217d2ee .generated_files/flags/default/a733305486dba52bf1b2f0129eacaac696315869
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/I2C.o.d 
	@${RM} ${OBJECTDIR}/I2C.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  I2C.c  -o ${OBJECTDIR}/I2C.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/I2C.o.d"        -g -omf=elf -DXPRJ_default=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -O0 -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
${OBJECTDIR}/GPS.o: GPS.c  .generated_files/flags/default/2a8f4a48840d747b70f7deec8eb66685d3f8a5ff .generated_files/flags/default/a733305486dba52bf1b2f0129eacaac696315869
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/GPS.o.d 
	@${RM} ${OBJECTDIR}/GPS.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  GPS.c  -o ${OBJECTDIR}/GPS.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/GPS.o.d"        -g -omf=elf -DXPRJ_default=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -O0 -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
${OBJECTDIR}/SPI.o: SPI.c  .generated_files/flags/default/be2112005903cea801f70a82e626c44962720204 .generated_files/flags/default/a733305486dba52bf1b2f0129eacaac696315869
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/SPI.o.d 
	@${RM} ${OBJECTDIR}/SPI.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  SPI.c  -o ${OBJECTDIR}/SPI.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/SPI.o.d"        -g -omf=elf -DXPRJ_default=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -O0 -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
${OBJECTDIR}/Interpreteur.o: Interpreteur.c  .generated_files/flags/default/7fd35b0feb0bbc7d9c6410a05592ade3ed73265e .generated_files/flags/default/a733305486dba52bf1b2f0129eacaac696315869
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/Interpreteur.o.d 
	@${RM} ${OBJECTDIR}/Interpreteur.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  Interpreteur.c  -o ${OBJECTDIR}/Interpreteur.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/Interpreteur.o.d"        -g -omf=elf -DXPRJ_default=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -O0 -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
${OBJECTDIR}/RF.o: RF.c  .generated_files/flags/default/3a97fc987e3b7eecc62f810a813ec491c2df1eae .generated_files/flags/default/a733305486dba52bf1b2f0129eacaac696315869
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/RF.o.d 
	@${RM} ${OBJECTDIR}/RF.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  RF.c  -o ${OBJECTDIR}/RF.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/RF.o.d"        -g -omf=elf -DXPRJ_default=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -O0 -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
${OBJECTDIR}/RF_Calib.o: RF_Calib.c  .generated_files/flags/default/736eda4c91473cb72daf7ebd96c1f2f367d1f05 .generated_files/flags/default/a733305486dba52bf1b2f0129eacaac696315869
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/RF_Calib.o.d 
	@${RM} ${OBJECTDIR}/RF_Calib.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  RF_Calib.c  -o ${OBJECTDIR}/RF_Calib.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/RF_Calib.o.d"        -g -omf=elf -DXPRJ_default=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -O0 -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
${OBJECTDIR}/RF_Test.o: RF_Test.c  .generated_files/flags/default/b8322a3adda9906c616a3b86c9836548e89221b5 .generated_files/flags/default/a733305486dba52bf1b2f0129eacaac696315869
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/RF_Test.o.d 
	@${RM} ${OBJECTDIR}/RF_Test.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  RF_Test.c  -o ${OBJECTDIR}/RF_Test.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/RF_Test.o.d"        -g -omf=elf -DXPRJ_default=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -O0 -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
${OBJECTDIR}/I2C_Accel.o: I2C_Accel.c  .generated_files/flags/default/4e4566bb14a57cd4b460a5c32e15c42f22a023da .generated_files/flags/default/a733305486dba52bf1b2f0129eacaac696315869
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/I2C_Accel.o.d 
	@${RM} ${OBJECTDIR}/I2C_Accel.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  I2C_Accel.c  -o ${OBJECTDIR}/I2C_Accel.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/I2C_Accel.o.d"        -g -omf=elf -DXPRJ_default=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -O0 -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
${OBJECTDIR}/I2C_Alti.o: I2C_Alti.c  .generated_files/flags/default/d748241ec47ac3e8af564a0cce713cd27b4a0b9a .generated_files/flags/default/a733305486dba52bf1b2f0129eacaac696315869
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/I2C_Alti.o.d 
	@${RM} ${OBJECTDIR}/I2C_Alti.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  I2C_Alti.c  -o ${OBJECTDIR}/I2C_Alti.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/I2C_Alti.o.d"        -g -omf=elf -DXPRJ_default=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -O0 -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
endif

# ------------------------------------------------------------------------------------
# Rules for buildStep: assemble
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
else
endif

# ------------------------------------------------------------------------------------
# Rules for buildStep: assemblePreproc
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
else
endif

# ------------------------------------------------------------------------------------
# Rules for buildStep: link
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
dist/${CND_CONF}/${IMAGE_TYPE}/Drone.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}: ${OBJECTFILES}  nbproject/Makefile-${CND_CONF}.mk    
	@${MKDIR} dist/${CND_CONF}/${IMAGE_TYPE} 
	${MP_CC} $(MP_EXTRA_LD_PRE)  -o dist/${CND_CONF}/${IMAGE_TYPE}/Drone.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}  ${OBJECTFILES_QUOTED_IF_SPACED}      -mcpu=$(MP_PROCESSOR_OPTION)        -D__DEBUG=__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -omf=elf -DXPRJ_default=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)   -mreserve=data@0x800:0x81F -mreserve=data@0x820:0x821 -mreserve=data@0x822:0x823 -mreserve=data@0x824:0x825 -mreserve=data@0x826:0x84F   -Wl,,,--defsym=__MPLAB_BUILD=1,--defsym=__MPLAB_DEBUG=1,--defsym=__DEBUG=1,-D__DEBUG=__DEBUG,--defsym=__MPLAB_DEBUGGER_PK3=1,$(MP_LINKER_FILE_OPTION),--stack=16,--check-sections,--data-init,--pack-data,--handles,--isr,--no-gc-sections,--fill-upper=0,--stackguard=16,--no-force-link,--smart-io,-Map="${DISTDIR}/${PROJECTNAME}.${IMAGE_TYPE}.map",--report-mem,--memorysummary,dist/${CND_CONF}/${IMAGE_TYPE}/memoryfile.xml$(MP_EXTRA_LD_POST)  -mdfp="${DFP_DIR}/xc16" 
	
else
dist/${CND_CONF}/${IMAGE_TYPE}/Drone.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}: ${OBJECTFILES}  nbproject/Makefile-${CND_CONF}.mk   
	@${MKDIR} dist/${CND_CONF}/${IMAGE_TYPE} 
	${MP_CC} $(MP_EXTRA_LD_PRE)  -o dist/${CND_CONF}/${IMAGE_TYPE}/Drone.X.${IMAGE_TYPE}.${DEBUGGABLE_SUFFIX}  ${OBJECTFILES_QUOTED_IF_SPACED}      -mcpu=$(MP_PROCESSOR_OPTION)        -omf=elf -DXPRJ_default=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -Wl,,,--defsym=__MPLAB_BUILD=1,$(MP_LINKER_FILE_OPTION),--stack=16,--check-sections,--data-init,--pack-data,--handles,--isr,--no-gc-sections,--fill-upper=0,--stackguard=16,--no-force-link,--smart-io,-Map="${DISTDIR}/${PROJECTNAME}.${IMAGE_TYPE}.map",--report-mem,--memorysummary,dist/${CND_CONF}/${IMAGE_TYPE}/memoryfile.xml$(MP_EXTRA_LD_POST)  -mdfp="${DFP_DIR}/xc16" 
	${MP_CC_DIR}\\xc16-bin2hex dist/${CND_CONF}/${IMAGE_TYPE}/Drone.X.${IMAGE_TYPE}.${DEBUGGABLE_SUFFIX} -a  -omf=elf   -mdfp="${DFP_DIR}/xc16" 
	
endif


# Subprojects
.build-subprojects:


# Subprojects
.clean-subprojects:

# Clean Targets
.clean-conf: ${CLEAN_SUBPROJECTS}
	${RM} -r build/default
	${RM} -r dist/default

# Enable dependency checking
.dep.inc: .depcheck-impl

DEPFILES=$(shell mplabwildcard ${POSSIBLE_DEPFILES})
ifneq (${DEPFILES},)
include ${DEPFILES}
endif
