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
FINAL_IMAGE=${DISTDIR}/fm1216me_fm_tuner.${IMAGE_TYPE}.${OUTPUT_SUFFIX}
else
IMAGE_TYPE=production
OUTPUT_SUFFIX=hex
DEBUGGABLE_SUFFIX=elf
FINAL_IMAGE=${DISTDIR}/fm1216me_fm_tuner.${IMAGE_TYPE}.${OUTPUT_SUFFIX}
endif

ifeq ($(COMPARE_BUILD), true)
COMPARISON_BUILD=--mafrlcsj
else
COMPARISON_BUILD=
endif

# Object Directory
OBJECTDIR=build/${CND_CONF}/${IMAGE_TYPE}

# Distribution Directory
DISTDIR=dist/${CND_CONF}/${IMAGE_TYPE}

# Source Files Quoted if spaced
SOURCEFILES_QUOTED_IF_SPACED=setup_pic16f876a.c main.c usart.c fm1216me.c usart_debug_board.c encoder_manager.c key_manager.c hd44780_pcf8574t.c keypad.c i2c_master.c

# Object Files Quoted if spaced
OBJECTFILES_QUOTED_IF_SPACED=${OBJECTDIR}/setup_pic16f876a.p1 ${OBJECTDIR}/main.p1 ${OBJECTDIR}/usart.p1 ${OBJECTDIR}/fm1216me.p1 ${OBJECTDIR}/usart_debug_board.p1 ${OBJECTDIR}/encoder_manager.p1 ${OBJECTDIR}/key_manager.p1 ${OBJECTDIR}/hd44780_pcf8574t.p1 ${OBJECTDIR}/keypad.p1 ${OBJECTDIR}/i2c_master.p1
POSSIBLE_DEPFILES=${OBJECTDIR}/setup_pic16f876a.p1.d ${OBJECTDIR}/main.p1.d ${OBJECTDIR}/usart.p1.d ${OBJECTDIR}/fm1216me.p1.d ${OBJECTDIR}/usart_debug_board.p1.d ${OBJECTDIR}/encoder_manager.p1.d ${OBJECTDIR}/key_manager.p1.d ${OBJECTDIR}/hd44780_pcf8574t.p1.d ${OBJECTDIR}/keypad.p1.d ${OBJECTDIR}/i2c_master.p1.d

# Object Files
OBJECTFILES=${OBJECTDIR}/setup_pic16f876a.p1 ${OBJECTDIR}/main.p1 ${OBJECTDIR}/usart.p1 ${OBJECTDIR}/fm1216me.p1 ${OBJECTDIR}/usart_debug_board.p1 ${OBJECTDIR}/encoder_manager.p1 ${OBJECTDIR}/key_manager.p1 ${OBJECTDIR}/hd44780_pcf8574t.p1 ${OBJECTDIR}/keypad.p1 ${OBJECTDIR}/i2c_master.p1

# Source Files
SOURCEFILES=setup_pic16f876a.c main.c usart.c fm1216me.c usart_debug_board.c encoder_manager.c key_manager.c hd44780_pcf8574t.c keypad.c i2c_master.c



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
	${MAKE}  -f nbproject/Makefile-default.mk ${DISTDIR}/fm1216me_fm_tuner.${IMAGE_TYPE}.${OUTPUT_SUFFIX}

MP_PROCESSOR_OPTION=16F876A
# ------------------------------------------------------------------------------------
# Rules for buildStep: compile
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
${OBJECTDIR}/setup_pic16f876a.p1: setup_pic16f876a.c  nbproject/Makefile-${CND_CONF}.mk 
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/setup_pic16f876a.p1.d 
	@${RM} ${OBJECTDIR}/setup_pic16f876a.p1 
	${MP_CC} --pass1 $(MP_EXTRA_CC_PRE) --chip=$(MP_PROCESSOR_OPTION) -Q -G  -D__DEBUG=1  --debugger=none    --double=24 --float=24 --opt=+asm,+asmfile,-speed,+space,+debug,-local --addrqual=require --mode=pro -P -N255 --warn=-3 --asmlist -DXPRJ_default=$(CND_CONF)  --summary=default,-psect,-class,+mem,-hex,-file --output=default,-inhx032 --runtime=default,+clear,+init,-keep,-no_startup,-osccal,-resetbits,-download,-stackcall,-config,+clib $(COMPARISON_BUILD)  --output=-mcof,+elf:multilocs --stack=compiled:auto:auto "--errformat=%f:%l: error: (%n) %s" "--warnformat=%f:%l: warning: (%n) %s" "--msgformat=%f:%l: advisory: (%n) %s"     -o${OBJECTDIR}/setup_pic16f876a.p1 setup_pic16f876a.c 
	@-${MV} ${OBJECTDIR}/setup_pic16f876a.d ${OBJECTDIR}/setup_pic16f876a.p1.d 
	@${FIXDEPS} ${OBJECTDIR}/setup_pic16f876a.p1.d $(SILENT) -rsi ${MP_CC_DIR}../  
	
${OBJECTDIR}/main.p1: main.c  nbproject/Makefile-${CND_CONF}.mk 
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/main.p1.d 
	@${RM} ${OBJECTDIR}/main.p1 
	${MP_CC} --pass1 $(MP_EXTRA_CC_PRE) --chip=$(MP_PROCESSOR_OPTION) -Q -G  -D__DEBUG=1  --debugger=none    --double=24 --float=24 --opt=+asm,+asmfile,-speed,+space,+debug,-local --addrqual=require --mode=pro -P -N255 --warn=-3 --asmlist -DXPRJ_default=$(CND_CONF)  --summary=default,-psect,-class,+mem,-hex,-file --output=default,-inhx032 --runtime=default,+clear,+init,-keep,-no_startup,-osccal,-resetbits,-download,-stackcall,-config,+clib $(COMPARISON_BUILD)  --output=-mcof,+elf:multilocs --stack=compiled:auto:auto "--errformat=%f:%l: error: (%n) %s" "--warnformat=%f:%l: warning: (%n) %s" "--msgformat=%f:%l: advisory: (%n) %s"     -o${OBJECTDIR}/main.p1 main.c 
	@-${MV} ${OBJECTDIR}/main.d ${OBJECTDIR}/main.p1.d 
	@${FIXDEPS} ${OBJECTDIR}/main.p1.d $(SILENT) -rsi ${MP_CC_DIR}../  
	
${OBJECTDIR}/usart.p1: usart.c  nbproject/Makefile-${CND_CONF}.mk 
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/usart.p1.d 
	@${RM} ${OBJECTDIR}/usart.p1 
	${MP_CC} --pass1 $(MP_EXTRA_CC_PRE) --chip=$(MP_PROCESSOR_OPTION) -Q -G  -D__DEBUG=1  --debugger=none    --double=24 --float=24 --opt=+asm,+asmfile,-speed,+space,+debug,-local --addrqual=require --mode=pro -P -N255 --warn=-3 --asmlist -DXPRJ_default=$(CND_CONF)  --summary=default,-psect,-class,+mem,-hex,-file --output=default,-inhx032 --runtime=default,+clear,+init,-keep,-no_startup,-osccal,-resetbits,-download,-stackcall,-config,+clib $(COMPARISON_BUILD)  --output=-mcof,+elf:multilocs --stack=compiled:auto:auto "--errformat=%f:%l: error: (%n) %s" "--warnformat=%f:%l: warning: (%n) %s" "--msgformat=%f:%l: advisory: (%n) %s"     -o${OBJECTDIR}/usart.p1 usart.c 
	@-${MV} ${OBJECTDIR}/usart.d ${OBJECTDIR}/usart.p1.d 
	@${FIXDEPS} ${OBJECTDIR}/usart.p1.d $(SILENT) -rsi ${MP_CC_DIR}../  
	
${OBJECTDIR}/fm1216me.p1: fm1216me.c  nbproject/Makefile-${CND_CONF}.mk 
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/fm1216me.p1.d 
	@${RM} ${OBJECTDIR}/fm1216me.p1 
	${MP_CC} --pass1 $(MP_EXTRA_CC_PRE) --chip=$(MP_PROCESSOR_OPTION) -Q -G  -D__DEBUG=1  --debugger=none    --double=24 --float=24 --opt=+asm,+asmfile,-speed,+space,+debug,-local --addrqual=require --mode=pro -P -N255 --warn=-3 --asmlist -DXPRJ_default=$(CND_CONF)  --summary=default,-psect,-class,+mem,-hex,-file --output=default,-inhx032 --runtime=default,+clear,+init,-keep,-no_startup,-osccal,-resetbits,-download,-stackcall,-config,+clib $(COMPARISON_BUILD)  --output=-mcof,+elf:multilocs --stack=compiled:auto:auto "--errformat=%f:%l: error: (%n) %s" "--warnformat=%f:%l: warning: (%n) %s" "--msgformat=%f:%l: advisory: (%n) %s"     -o${OBJECTDIR}/fm1216me.p1 fm1216me.c 
	@-${MV} ${OBJECTDIR}/fm1216me.d ${OBJECTDIR}/fm1216me.p1.d 
	@${FIXDEPS} ${OBJECTDIR}/fm1216me.p1.d $(SILENT) -rsi ${MP_CC_DIR}../  
	
${OBJECTDIR}/usart_debug_board.p1: usart_debug_board.c  nbproject/Makefile-${CND_CONF}.mk 
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/usart_debug_board.p1.d 
	@${RM} ${OBJECTDIR}/usart_debug_board.p1 
	${MP_CC} --pass1 $(MP_EXTRA_CC_PRE) --chip=$(MP_PROCESSOR_OPTION) -Q -G  -D__DEBUG=1  --debugger=none    --double=24 --float=24 --opt=+asm,+asmfile,-speed,+space,+debug,-local --addrqual=require --mode=pro -P -N255 --warn=-3 --asmlist -DXPRJ_default=$(CND_CONF)  --summary=default,-psect,-class,+mem,-hex,-file --output=default,-inhx032 --runtime=default,+clear,+init,-keep,-no_startup,-osccal,-resetbits,-download,-stackcall,-config,+clib $(COMPARISON_BUILD)  --output=-mcof,+elf:multilocs --stack=compiled:auto:auto "--errformat=%f:%l: error: (%n) %s" "--warnformat=%f:%l: warning: (%n) %s" "--msgformat=%f:%l: advisory: (%n) %s"     -o${OBJECTDIR}/usart_debug_board.p1 usart_debug_board.c 
	@-${MV} ${OBJECTDIR}/usart_debug_board.d ${OBJECTDIR}/usart_debug_board.p1.d 
	@${FIXDEPS} ${OBJECTDIR}/usart_debug_board.p1.d $(SILENT) -rsi ${MP_CC_DIR}../  
	
${OBJECTDIR}/encoder_manager.p1: encoder_manager.c  nbproject/Makefile-${CND_CONF}.mk 
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/encoder_manager.p1.d 
	@${RM} ${OBJECTDIR}/encoder_manager.p1 
	${MP_CC} --pass1 $(MP_EXTRA_CC_PRE) --chip=$(MP_PROCESSOR_OPTION) -Q -G  -D__DEBUG=1  --debugger=none    --double=24 --float=24 --opt=+asm,+asmfile,-speed,+space,+debug,-local --addrqual=require --mode=pro -P -N255 --warn=-3 --asmlist -DXPRJ_default=$(CND_CONF)  --summary=default,-psect,-class,+mem,-hex,-file --output=default,-inhx032 --runtime=default,+clear,+init,-keep,-no_startup,-osccal,-resetbits,-download,-stackcall,-config,+clib $(COMPARISON_BUILD)  --output=-mcof,+elf:multilocs --stack=compiled:auto:auto "--errformat=%f:%l: error: (%n) %s" "--warnformat=%f:%l: warning: (%n) %s" "--msgformat=%f:%l: advisory: (%n) %s"     -o${OBJECTDIR}/encoder_manager.p1 encoder_manager.c 
	@-${MV} ${OBJECTDIR}/encoder_manager.d ${OBJECTDIR}/encoder_manager.p1.d 
	@${FIXDEPS} ${OBJECTDIR}/encoder_manager.p1.d $(SILENT) -rsi ${MP_CC_DIR}../  
	
${OBJECTDIR}/key_manager.p1: key_manager.c  nbproject/Makefile-${CND_CONF}.mk 
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/key_manager.p1.d 
	@${RM} ${OBJECTDIR}/key_manager.p1 
	${MP_CC} --pass1 $(MP_EXTRA_CC_PRE) --chip=$(MP_PROCESSOR_OPTION) -Q -G  -D__DEBUG=1  --debugger=none    --double=24 --float=24 --opt=+asm,+asmfile,-speed,+space,+debug,-local --addrqual=require --mode=pro -P -N255 --warn=-3 --asmlist -DXPRJ_default=$(CND_CONF)  --summary=default,-psect,-class,+mem,-hex,-file --output=default,-inhx032 --runtime=default,+clear,+init,-keep,-no_startup,-osccal,-resetbits,-download,-stackcall,-config,+clib $(COMPARISON_BUILD)  --output=-mcof,+elf:multilocs --stack=compiled:auto:auto "--errformat=%f:%l: error: (%n) %s" "--warnformat=%f:%l: warning: (%n) %s" "--msgformat=%f:%l: advisory: (%n) %s"     -o${OBJECTDIR}/key_manager.p1 key_manager.c 
	@-${MV} ${OBJECTDIR}/key_manager.d ${OBJECTDIR}/key_manager.p1.d 
	@${FIXDEPS} ${OBJECTDIR}/key_manager.p1.d $(SILENT) -rsi ${MP_CC_DIR}../  
	
${OBJECTDIR}/hd44780_pcf8574t.p1: hd44780_pcf8574t.c  nbproject/Makefile-${CND_CONF}.mk 
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/hd44780_pcf8574t.p1.d 
	@${RM} ${OBJECTDIR}/hd44780_pcf8574t.p1 
	${MP_CC} --pass1 $(MP_EXTRA_CC_PRE) --chip=$(MP_PROCESSOR_OPTION) -Q -G  -D__DEBUG=1  --debugger=none    --double=24 --float=24 --opt=+asm,+asmfile,-speed,+space,+debug,-local --addrqual=require --mode=pro -P -N255 --warn=-3 --asmlist -DXPRJ_default=$(CND_CONF)  --summary=default,-psect,-class,+mem,-hex,-file --output=default,-inhx032 --runtime=default,+clear,+init,-keep,-no_startup,-osccal,-resetbits,-download,-stackcall,-config,+clib $(COMPARISON_BUILD)  --output=-mcof,+elf:multilocs --stack=compiled:auto:auto "--errformat=%f:%l: error: (%n) %s" "--warnformat=%f:%l: warning: (%n) %s" "--msgformat=%f:%l: advisory: (%n) %s"     -o${OBJECTDIR}/hd44780_pcf8574t.p1 hd44780_pcf8574t.c 
	@-${MV} ${OBJECTDIR}/hd44780_pcf8574t.d ${OBJECTDIR}/hd44780_pcf8574t.p1.d 
	@${FIXDEPS} ${OBJECTDIR}/hd44780_pcf8574t.p1.d $(SILENT) -rsi ${MP_CC_DIR}../  
	
${OBJECTDIR}/keypad.p1: keypad.c  nbproject/Makefile-${CND_CONF}.mk 
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/keypad.p1.d 
	@${RM} ${OBJECTDIR}/keypad.p1 
	${MP_CC} --pass1 $(MP_EXTRA_CC_PRE) --chip=$(MP_PROCESSOR_OPTION) -Q -G  -D__DEBUG=1  --debugger=none    --double=24 --float=24 --opt=+asm,+asmfile,-speed,+space,+debug,-local --addrqual=require --mode=pro -P -N255 --warn=-3 --asmlist -DXPRJ_default=$(CND_CONF)  --summary=default,-psect,-class,+mem,-hex,-file --output=default,-inhx032 --runtime=default,+clear,+init,-keep,-no_startup,-osccal,-resetbits,-download,-stackcall,-config,+clib $(COMPARISON_BUILD)  --output=-mcof,+elf:multilocs --stack=compiled:auto:auto "--errformat=%f:%l: error: (%n) %s" "--warnformat=%f:%l: warning: (%n) %s" "--msgformat=%f:%l: advisory: (%n) %s"     -o${OBJECTDIR}/keypad.p1 keypad.c 
	@-${MV} ${OBJECTDIR}/keypad.d ${OBJECTDIR}/keypad.p1.d 
	@${FIXDEPS} ${OBJECTDIR}/keypad.p1.d $(SILENT) -rsi ${MP_CC_DIR}../  
	
${OBJECTDIR}/i2c_master.p1: i2c_master.c  nbproject/Makefile-${CND_CONF}.mk 
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/i2c_master.p1.d 
	@${RM} ${OBJECTDIR}/i2c_master.p1 
	${MP_CC} --pass1 $(MP_EXTRA_CC_PRE) --chip=$(MP_PROCESSOR_OPTION) -Q -G  -D__DEBUG=1  --debugger=none    --double=24 --float=24 --opt=+asm,+asmfile,-speed,+space,+debug,-local --addrqual=require --mode=pro -P -N255 --warn=-3 --asmlist -DXPRJ_default=$(CND_CONF)  --summary=default,-psect,-class,+mem,-hex,-file --output=default,-inhx032 --runtime=default,+clear,+init,-keep,-no_startup,-osccal,-resetbits,-download,-stackcall,-config,+clib $(COMPARISON_BUILD)  --output=-mcof,+elf:multilocs --stack=compiled:auto:auto "--errformat=%f:%l: error: (%n) %s" "--warnformat=%f:%l: warning: (%n) %s" "--msgformat=%f:%l: advisory: (%n) %s"     -o${OBJECTDIR}/i2c_master.p1 i2c_master.c 
	@-${MV} ${OBJECTDIR}/i2c_master.d ${OBJECTDIR}/i2c_master.p1.d 
	@${FIXDEPS} ${OBJECTDIR}/i2c_master.p1.d $(SILENT) -rsi ${MP_CC_DIR}../  
	
else
${OBJECTDIR}/setup_pic16f876a.p1: setup_pic16f876a.c  nbproject/Makefile-${CND_CONF}.mk 
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/setup_pic16f876a.p1.d 
	@${RM} ${OBJECTDIR}/setup_pic16f876a.p1 
	${MP_CC} --pass1 $(MP_EXTRA_CC_PRE) --chip=$(MP_PROCESSOR_OPTION) -Q -G    --double=24 --float=24 --opt=+asm,+asmfile,-speed,+space,+debug,-local --addrqual=require --mode=pro -P -N255 --warn=-3 --asmlist -DXPRJ_default=$(CND_CONF)  --summary=default,-psect,-class,+mem,-hex,-file --output=default,-inhx032 --runtime=default,+clear,+init,-keep,-no_startup,-osccal,-resetbits,-download,-stackcall,-config,+clib $(COMPARISON_BUILD)  --output=-mcof,+elf:multilocs --stack=compiled:auto:auto "--errformat=%f:%l: error: (%n) %s" "--warnformat=%f:%l: warning: (%n) %s" "--msgformat=%f:%l: advisory: (%n) %s"     -o${OBJECTDIR}/setup_pic16f876a.p1 setup_pic16f876a.c 
	@-${MV} ${OBJECTDIR}/setup_pic16f876a.d ${OBJECTDIR}/setup_pic16f876a.p1.d 
	@${FIXDEPS} ${OBJECTDIR}/setup_pic16f876a.p1.d $(SILENT) -rsi ${MP_CC_DIR}../  
	
${OBJECTDIR}/main.p1: main.c  nbproject/Makefile-${CND_CONF}.mk 
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/main.p1.d 
	@${RM} ${OBJECTDIR}/main.p1 
	${MP_CC} --pass1 $(MP_EXTRA_CC_PRE) --chip=$(MP_PROCESSOR_OPTION) -Q -G    --double=24 --float=24 --opt=+asm,+asmfile,-speed,+space,+debug,-local --addrqual=require --mode=pro -P -N255 --warn=-3 --asmlist -DXPRJ_default=$(CND_CONF)  --summary=default,-psect,-class,+mem,-hex,-file --output=default,-inhx032 --runtime=default,+clear,+init,-keep,-no_startup,-osccal,-resetbits,-download,-stackcall,-config,+clib $(COMPARISON_BUILD)  --output=-mcof,+elf:multilocs --stack=compiled:auto:auto "--errformat=%f:%l: error: (%n) %s" "--warnformat=%f:%l: warning: (%n) %s" "--msgformat=%f:%l: advisory: (%n) %s"     -o${OBJECTDIR}/main.p1 main.c 
	@-${MV} ${OBJECTDIR}/main.d ${OBJECTDIR}/main.p1.d 
	@${FIXDEPS} ${OBJECTDIR}/main.p1.d $(SILENT) -rsi ${MP_CC_DIR}../  
	
${OBJECTDIR}/usart.p1: usart.c  nbproject/Makefile-${CND_CONF}.mk 
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/usart.p1.d 
	@${RM} ${OBJECTDIR}/usart.p1 
	${MP_CC} --pass1 $(MP_EXTRA_CC_PRE) --chip=$(MP_PROCESSOR_OPTION) -Q -G    --double=24 --float=24 --opt=+asm,+asmfile,-speed,+space,+debug,-local --addrqual=require --mode=pro -P -N255 --warn=-3 --asmlist -DXPRJ_default=$(CND_CONF)  --summary=default,-psect,-class,+mem,-hex,-file --output=default,-inhx032 --runtime=default,+clear,+init,-keep,-no_startup,-osccal,-resetbits,-download,-stackcall,-config,+clib $(COMPARISON_BUILD)  --output=-mcof,+elf:multilocs --stack=compiled:auto:auto "--errformat=%f:%l: error: (%n) %s" "--warnformat=%f:%l: warning: (%n) %s" "--msgformat=%f:%l: advisory: (%n) %s"     -o${OBJECTDIR}/usart.p1 usart.c 
	@-${MV} ${OBJECTDIR}/usart.d ${OBJECTDIR}/usart.p1.d 
	@${FIXDEPS} ${OBJECTDIR}/usart.p1.d $(SILENT) -rsi ${MP_CC_DIR}../  
	
${OBJECTDIR}/fm1216me.p1: fm1216me.c  nbproject/Makefile-${CND_CONF}.mk 
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/fm1216me.p1.d 
	@${RM} ${OBJECTDIR}/fm1216me.p1 
	${MP_CC} --pass1 $(MP_EXTRA_CC_PRE) --chip=$(MP_PROCESSOR_OPTION) -Q -G    --double=24 --float=24 --opt=+asm,+asmfile,-speed,+space,+debug,-local --addrqual=require --mode=pro -P -N255 --warn=-3 --asmlist -DXPRJ_default=$(CND_CONF)  --summary=default,-psect,-class,+mem,-hex,-file --output=default,-inhx032 --runtime=default,+clear,+init,-keep,-no_startup,-osccal,-resetbits,-download,-stackcall,-config,+clib $(COMPARISON_BUILD)  --output=-mcof,+elf:multilocs --stack=compiled:auto:auto "--errformat=%f:%l: error: (%n) %s" "--warnformat=%f:%l: warning: (%n) %s" "--msgformat=%f:%l: advisory: (%n) %s"     -o${OBJECTDIR}/fm1216me.p1 fm1216me.c 
	@-${MV} ${OBJECTDIR}/fm1216me.d ${OBJECTDIR}/fm1216me.p1.d 
	@${FIXDEPS} ${OBJECTDIR}/fm1216me.p1.d $(SILENT) -rsi ${MP_CC_DIR}../  
	
${OBJECTDIR}/usart_debug_board.p1: usart_debug_board.c  nbproject/Makefile-${CND_CONF}.mk 
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/usart_debug_board.p1.d 
	@${RM} ${OBJECTDIR}/usart_debug_board.p1 
	${MP_CC} --pass1 $(MP_EXTRA_CC_PRE) --chip=$(MP_PROCESSOR_OPTION) -Q -G    --double=24 --float=24 --opt=+asm,+asmfile,-speed,+space,+debug,-local --addrqual=require --mode=pro -P -N255 --warn=-3 --asmlist -DXPRJ_default=$(CND_CONF)  --summary=default,-psect,-class,+mem,-hex,-file --output=default,-inhx032 --runtime=default,+clear,+init,-keep,-no_startup,-osccal,-resetbits,-download,-stackcall,-config,+clib $(COMPARISON_BUILD)  --output=-mcof,+elf:multilocs --stack=compiled:auto:auto "--errformat=%f:%l: error: (%n) %s" "--warnformat=%f:%l: warning: (%n) %s" "--msgformat=%f:%l: advisory: (%n) %s"     -o${OBJECTDIR}/usart_debug_board.p1 usart_debug_board.c 
	@-${MV} ${OBJECTDIR}/usart_debug_board.d ${OBJECTDIR}/usart_debug_board.p1.d 
	@${FIXDEPS} ${OBJECTDIR}/usart_debug_board.p1.d $(SILENT) -rsi ${MP_CC_DIR}../  
	
${OBJECTDIR}/encoder_manager.p1: encoder_manager.c  nbproject/Makefile-${CND_CONF}.mk 
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/encoder_manager.p1.d 
	@${RM} ${OBJECTDIR}/encoder_manager.p1 
	${MP_CC} --pass1 $(MP_EXTRA_CC_PRE) --chip=$(MP_PROCESSOR_OPTION) -Q -G    --double=24 --float=24 --opt=+asm,+asmfile,-speed,+space,+debug,-local --addrqual=require --mode=pro -P -N255 --warn=-3 --asmlist -DXPRJ_default=$(CND_CONF)  --summary=default,-psect,-class,+mem,-hex,-file --output=default,-inhx032 --runtime=default,+clear,+init,-keep,-no_startup,-osccal,-resetbits,-download,-stackcall,-config,+clib $(COMPARISON_BUILD)  --output=-mcof,+elf:multilocs --stack=compiled:auto:auto "--errformat=%f:%l: error: (%n) %s" "--warnformat=%f:%l: warning: (%n) %s" "--msgformat=%f:%l: advisory: (%n) %s"     -o${OBJECTDIR}/encoder_manager.p1 encoder_manager.c 
	@-${MV} ${OBJECTDIR}/encoder_manager.d ${OBJECTDIR}/encoder_manager.p1.d 
	@${FIXDEPS} ${OBJECTDIR}/encoder_manager.p1.d $(SILENT) -rsi ${MP_CC_DIR}../  
	
${OBJECTDIR}/key_manager.p1: key_manager.c  nbproject/Makefile-${CND_CONF}.mk 
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/key_manager.p1.d 
	@${RM} ${OBJECTDIR}/key_manager.p1 
	${MP_CC} --pass1 $(MP_EXTRA_CC_PRE) --chip=$(MP_PROCESSOR_OPTION) -Q -G    --double=24 --float=24 --opt=+asm,+asmfile,-speed,+space,+debug,-local --addrqual=require --mode=pro -P -N255 --warn=-3 --asmlist -DXPRJ_default=$(CND_CONF)  --summary=default,-psect,-class,+mem,-hex,-file --output=default,-inhx032 --runtime=default,+clear,+init,-keep,-no_startup,-osccal,-resetbits,-download,-stackcall,-config,+clib $(COMPARISON_BUILD)  --output=-mcof,+elf:multilocs --stack=compiled:auto:auto "--errformat=%f:%l: error: (%n) %s" "--warnformat=%f:%l: warning: (%n) %s" "--msgformat=%f:%l: advisory: (%n) %s"     -o${OBJECTDIR}/key_manager.p1 key_manager.c 
	@-${MV} ${OBJECTDIR}/key_manager.d ${OBJECTDIR}/key_manager.p1.d 
	@${FIXDEPS} ${OBJECTDIR}/key_manager.p1.d $(SILENT) -rsi ${MP_CC_DIR}../  
	
${OBJECTDIR}/hd44780_pcf8574t.p1: hd44780_pcf8574t.c  nbproject/Makefile-${CND_CONF}.mk 
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/hd44780_pcf8574t.p1.d 
	@${RM} ${OBJECTDIR}/hd44780_pcf8574t.p1 
	${MP_CC} --pass1 $(MP_EXTRA_CC_PRE) --chip=$(MP_PROCESSOR_OPTION) -Q -G    --double=24 --float=24 --opt=+asm,+asmfile,-speed,+space,+debug,-local --addrqual=require --mode=pro -P -N255 --warn=-3 --asmlist -DXPRJ_default=$(CND_CONF)  --summary=default,-psect,-class,+mem,-hex,-file --output=default,-inhx032 --runtime=default,+clear,+init,-keep,-no_startup,-osccal,-resetbits,-download,-stackcall,-config,+clib $(COMPARISON_BUILD)  --output=-mcof,+elf:multilocs --stack=compiled:auto:auto "--errformat=%f:%l: error: (%n) %s" "--warnformat=%f:%l: warning: (%n) %s" "--msgformat=%f:%l: advisory: (%n) %s"     -o${OBJECTDIR}/hd44780_pcf8574t.p1 hd44780_pcf8574t.c 
	@-${MV} ${OBJECTDIR}/hd44780_pcf8574t.d ${OBJECTDIR}/hd44780_pcf8574t.p1.d 
	@${FIXDEPS} ${OBJECTDIR}/hd44780_pcf8574t.p1.d $(SILENT) -rsi ${MP_CC_DIR}../  
	
${OBJECTDIR}/keypad.p1: keypad.c  nbproject/Makefile-${CND_CONF}.mk 
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/keypad.p1.d 
	@${RM} ${OBJECTDIR}/keypad.p1 
	${MP_CC} --pass1 $(MP_EXTRA_CC_PRE) --chip=$(MP_PROCESSOR_OPTION) -Q -G    --double=24 --float=24 --opt=+asm,+asmfile,-speed,+space,+debug,-local --addrqual=require --mode=pro -P -N255 --warn=-3 --asmlist -DXPRJ_default=$(CND_CONF)  --summary=default,-psect,-class,+mem,-hex,-file --output=default,-inhx032 --runtime=default,+clear,+init,-keep,-no_startup,-osccal,-resetbits,-download,-stackcall,-config,+clib $(COMPARISON_BUILD)  --output=-mcof,+elf:multilocs --stack=compiled:auto:auto "--errformat=%f:%l: error: (%n) %s" "--warnformat=%f:%l: warning: (%n) %s" "--msgformat=%f:%l: advisory: (%n) %s"     -o${OBJECTDIR}/keypad.p1 keypad.c 
	@-${MV} ${OBJECTDIR}/keypad.d ${OBJECTDIR}/keypad.p1.d 
	@${FIXDEPS} ${OBJECTDIR}/keypad.p1.d $(SILENT) -rsi ${MP_CC_DIR}../  
	
${OBJECTDIR}/i2c_master.p1: i2c_master.c  nbproject/Makefile-${CND_CONF}.mk 
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/i2c_master.p1.d 
	@${RM} ${OBJECTDIR}/i2c_master.p1 
	${MP_CC} --pass1 $(MP_EXTRA_CC_PRE) --chip=$(MP_PROCESSOR_OPTION) -Q -G    --double=24 --float=24 --opt=+asm,+asmfile,-speed,+space,+debug,-local --addrqual=require --mode=pro -P -N255 --warn=-3 --asmlist -DXPRJ_default=$(CND_CONF)  --summary=default,-psect,-class,+mem,-hex,-file --output=default,-inhx032 --runtime=default,+clear,+init,-keep,-no_startup,-osccal,-resetbits,-download,-stackcall,-config,+clib $(COMPARISON_BUILD)  --output=-mcof,+elf:multilocs --stack=compiled:auto:auto "--errformat=%f:%l: error: (%n) %s" "--warnformat=%f:%l: warning: (%n) %s" "--msgformat=%f:%l: advisory: (%n) %s"     -o${OBJECTDIR}/i2c_master.p1 i2c_master.c 
	@-${MV} ${OBJECTDIR}/i2c_master.d ${OBJECTDIR}/i2c_master.p1.d 
	@${FIXDEPS} ${OBJECTDIR}/i2c_master.p1.d $(SILENT) -rsi ${MP_CC_DIR}../  
	
endif

# ------------------------------------------------------------------------------------
# Rules for buildStep: assemble
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
else
endif

# ------------------------------------------------------------------------------------
# Rules for buildStep: link
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
${DISTDIR}/fm1216me_fm_tuner.${IMAGE_TYPE}.${OUTPUT_SUFFIX}: ${OBJECTFILES}  nbproject/Makefile-${CND_CONF}.mk    
	@${MKDIR} ${DISTDIR} 
	${MP_CC} $(MP_EXTRA_LD_PRE) --chip=$(MP_PROCESSOR_OPTION) -G -m${DISTDIR}/fm1216me_fm_tuner.${IMAGE_TYPE}.map  -D__DEBUG=1  --debugger=none  -DXPRJ_default=$(CND_CONF)    --double=24 --float=24 --opt=+asm,+asmfile,-speed,+space,+debug,-local --addrqual=require --mode=pro -P -N255 --warn=-3 --asmlist --summary=default,-psect,-class,+mem,-hex,-file --output=default,-inhx032 --runtime=default,+clear,+init,-keep,-no_startup,-osccal,-resetbits,-download,-stackcall,-config,+clib --output=-mcof,+elf:multilocs --stack=compiled:auto:auto "--errformat=%f:%l: error: (%n) %s" "--warnformat=%f:%l: warning: (%n) %s" "--msgformat=%f:%l: advisory: (%n) %s"        $(COMPARISON_BUILD) --memorysummary ${DISTDIR}/memoryfile.xml -o${DISTDIR}/fm1216me_fm_tuner.${IMAGE_TYPE}.${DEBUGGABLE_SUFFIX}  ${OBJECTFILES_QUOTED_IF_SPACED}     
	@${RM} ${DISTDIR}/fm1216me_fm_tuner.${IMAGE_TYPE}.hex 
	
	
else
${DISTDIR}/fm1216me_fm_tuner.${IMAGE_TYPE}.${OUTPUT_SUFFIX}: ${OBJECTFILES}  nbproject/Makefile-${CND_CONF}.mk   
	@${MKDIR} ${DISTDIR} 
	${MP_CC} $(MP_EXTRA_LD_PRE) --chip=$(MP_PROCESSOR_OPTION) -G -m${DISTDIR}/fm1216me_fm_tuner.${IMAGE_TYPE}.map  -DXPRJ_default=$(CND_CONF)    --double=24 --float=24 --opt=+asm,+asmfile,-speed,+space,+debug,-local --addrqual=require --mode=pro -P -N255 --warn=-3 --asmlist --summary=default,-psect,-class,+mem,-hex,-file --output=default,-inhx032 --runtime=default,+clear,+init,-keep,-no_startup,-osccal,-resetbits,-download,-stackcall,-config,+clib --output=-mcof,+elf:multilocs --stack=compiled:auto:auto "--errformat=%f:%l: error: (%n) %s" "--warnformat=%f:%l: warning: (%n) %s" "--msgformat=%f:%l: advisory: (%n) %s"     $(COMPARISON_BUILD) --memorysummary ${DISTDIR}/memoryfile.xml -o${DISTDIR}/fm1216me_fm_tuner.${IMAGE_TYPE}.${DEBUGGABLE_SUFFIX}  ${OBJECTFILES_QUOTED_IF_SPACED}     
	
	
endif


# Subprojects
.build-subprojects:


# Subprojects
.clean-subprojects:

# Clean Targets
.clean-conf: ${CLEAN_SUBPROJECTS}
	${RM} -r ${OBJECTDIR}
	${RM} -r ${DISTDIR}

# Enable dependency checking
.dep.inc: .depcheck-impl

DEPFILES=$(wildcard ${POSSIBLE_DEPFILES})
ifneq (${DEPFILES},)
include ${DEPFILES}
endif
