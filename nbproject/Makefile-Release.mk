#
# Generated Makefile - do not edit!
#
# Edit the Makefile in the project folder instead (../Makefile). Each target
# has a -pre and a -post target defined where you can add customized code.
#
# This makefile implements configuration specific macros and targets.


# Environment
MKDIR=mkdir
CP=cp
GREP=grep
NM=nm
CCADMIN=CCadmin
RANLIB=ranlib
CC=gcc
CCC=g++
CXX=g++
FC=gfortran
AS=as

# Macros
CND_PLATFORM=GNU-Linux
CND_DLIB_EXT=so
CND_CONF=Release
CND_DISTDIR=dist
CND_BUILDDIR=build

# Include project Makefile
include Makefile

# Object Directory
OBJECTDIR=${CND_BUILDDIR}/${CND_CONF}/${CND_PLATFORM}

# Object Files
OBJECTFILES= \
	${OBJECTDIR}/DconSender.o \
	${OBJECTDIR}/PanelSender.o \
	${OBJECTDIR}/Processor.o \
	${OBJECTDIR}/SerialSender.o \
	${OBJECTDIR}/SocketReceiver.o \
	${OBJECTDIR}/SocketSender.o \
	${OBJECTDIR}/module_new.o


# C Compiler Flags
CFLAGS=

# CC Compiler Flags
CCFLAGS=
CXXFLAGS=

# Fortran Compiler Flags
FFLAGS=

# Assembler Flags
ASFLAGS=

# Link Libraries and Options
LDLIBSOPTIONS=

# Build Targets
.build-conf: ${BUILD_SUBPROJECTS}
	"${MAKE}"  -f nbproject/Makefile-${CND_CONF}.mk ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/libprocessor.a

${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/libprocessor.a: ${OBJECTFILES}
	${MKDIR} -p ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}
	${RM} ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/libprocessor.a
	${AR} -rv ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/libprocessor.a ${OBJECTFILES} 
	$(RANLIB) ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/libprocessor.a

${OBJECTDIR}/DconSender.o: DconSender.cpp nbproject/Makefile-${CND_CONF}.mk
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -I/usr/include/modbus -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/DconSender.o DconSender.cpp

${OBJECTDIR}/PanelSender.o: PanelSender.cpp nbproject/Makefile-${CND_CONF}.mk
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -I/usr/include/modbus -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/PanelSender.o PanelSender.cpp

${OBJECTDIR}/Processor.o: Processor.cpp nbproject/Makefile-${CND_CONF}.mk
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -I/usr/include/modbus -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/Processor.o Processor.cpp

${OBJECTDIR}/SerialSender.o: SerialSender.cpp nbproject/Makefile-${CND_CONF}.mk
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -I/usr/include/modbus -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/SerialSender.o SerialSender.cpp

${OBJECTDIR}/SocketReceiver.o: SocketReceiver.cpp nbproject/Makefile-${CND_CONF}.mk
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -I/usr/include/modbus -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/SocketReceiver.o SocketReceiver.cpp

${OBJECTDIR}/SocketSender.o: SocketSender.cpp nbproject/Makefile-${CND_CONF}.mk
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -I/usr/include/modbus -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/SocketSender.o SocketSender.cpp

${OBJECTDIR}/module_new.o: module_new.cpp nbproject/Makefile-${CND_CONF}.mk
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -I/usr/include/modbus -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/module_new.o module_new.cpp

# Subprojects
.build-subprojects:

# Clean Targets
.clean-conf: ${CLEAN_SUBPROJECTS}
	${RM} -r ${CND_BUILDDIR}/${CND_CONF}

# Subprojects
.clean-subprojects:

# Enable dependency checking
.dep.inc: .depcheck-impl

include .dep.inc
