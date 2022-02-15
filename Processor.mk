##
## Auto Generated makefile by CodeLite IDE
## any manual changes will be erased      
##
## Debug
ProjectName            :=Processor
ConfigurationName      :=Debug
WorkspacePath          :=/home/avmd/Documents/Work/Bulgaria
ProjectPath            :=/home/avmd/Documents/Work/Bulgaria/Processor
IntermediateDirectory  :=./Debug
OutDir                 := $(IntermediateDirectory)
CurrentFileName        :=
CurrentFilePath        :=
CurrentFileFullPath    :=
User                   :=viktor
Date                   :=15/02/22
CodeLitePath           :=/home/avmd/.codelite
LinkerName             :=/usr/bin/g++
SharedObjectLinkerName :=/usr/bin/g++ -shared -fPIC
ObjectSuffix           :=.o
DependSuffix           :=.o.d
PreprocessSuffix       :=.i
DebugSwitch            :=-g 
IncludeSwitch          :=-I
LibrarySwitch          :=-l
OutputSwitch           :=-o 
LibraryPathSwitch      :=-L
PreprocessorSwitch     :=-D
SourceSwitch           :=-c 
OutputFile             :=$(IntermediateDirectory)/lib$(ProjectName).a
Preprocessors          :=
ObjectSwitch           :=-o 
ArchiveOutputSwitch    := 
PreprocessOnlySwitch   :=-E
ObjectsFileList        :="Processor.txt"
PCHCompileFlags        :=
MakeDirCommand         :=mkdir -p
LinkOptions            :=  -lmodbus
IncludePath            :=  $(IncludeSwitch). $(IncludeSwitch). $(IncludeSwitch)/usr/include/modbus 
IncludePCH             := 
RcIncludePath          := 
Libs                   := $(LibrarySwitch)/usr/include/modbus/modbus.h 
ArLibs                 :=  "/usr/include/modbus/modbus.h" 
LibPath                := $(LibraryPathSwitch). $(LibraryPathSwitch)/usr/include/modbus 

##
## Common variables
## AR, CXX, CC, AS, CXXFLAGS and CFLAGS can be overriden using an environment variables
##
AR       := /usr/bin/ar rcu
CXX      := /usr/bin/g++
CC       := /usr/bin/gcc
CXXFLAGS :=  -g -O0 -Wall -lstdc++ -std=c++17 $(Preprocessors)
CFLAGS   :=  -g -O0 -Wall $(Preprocessors)
ASFLAGS  := 
AS       := /usr/bin/as


##
## User defined environment variables
##
CodeLiteDir:=/usr/share/codelite
Objects0=$(IntermediateDirectory)/DconSender.cpp$(ObjectSuffix) $(IntermediateDirectory)/PanelSender.cpp$(ObjectSuffix) $(IntermediateDirectory)/Processor.cpp$(ObjectSuffix) $(IntermediateDirectory)/SocketReceiver.cpp$(ObjectSuffix) $(IntermediateDirectory)/SocketSender.cpp$(ObjectSuffix) $(IntermediateDirectory)/SerialSender.cpp$(ObjectSuffix) 



Objects=$(Objects0) 

##
## Main Build Targets 
##
.PHONY: all clean PreBuild PrePreBuild PostBuild MakeIntermediateDirs
all: $(IntermediateDirectory) $(OutputFile)

$(OutputFile): $(Objects)
	@$(MakeDirCommand) $(@D)
	@echo "" > $(IntermediateDirectory)/.d
	@echo $(Objects0)  > $(ObjectsFileList)
	$(AR) $(ArchiveOutputSwitch)$(OutputFile) @$(ObjectsFileList) $(ArLibs)
	@$(MakeDirCommand) "/home/avmd/Documents/Work/Bulgaria/.build-debug"
	@echo rebuilt > "/home/avmd/Documents/Work/Bulgaria/.build-debug/Processor"

MakeIntermediateDirs:
	@test -d ./Debug || $(MakeDirCommand) ./Debug


./Debug:
	@test -d ./Debug || $(MakeDirCommand) ./Debug

PreBuild:


##
## Objects
##
$(IntermediateDirectory)/DconSender.cpp$(ObjectSuffix): DconSender.cpp $(IntermediateDirectory)/DconSender.cpp$(DependSuffix)
	$(CXX) $(IncludePCH) $(SourceSwitch) "/home/avmd/Documents/Work/Bulgaria/Processor/DconSender.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/DconSender.cpp$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/DconSender.cpp$(DependSuffix): DconSender.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/DconSender.cpp$(ObjectSuffix) -MF$(IntermediateDirectory)/DconSender.cpp$(DependSuffix) -MM DconSender.cpp

$(IntermediateDirectory)/DconSender.cpp$(PreprocessSuffix): DconSender.cpp
	$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/DconSender.cpp$(PreprocessSuffix) DconSender.cpp

$(IntermediateDirectory)/PanelSender.cpp$(ObjectSuffix): PanelSender.cpp $(IntermediateDirectory)/PanelSender.cpp$(DependSuffix)
	$(CXX) $(IncludePCH) $(SourceSwitch) "/home/avmd/Documents/Work/Bulgaria/Processor/PanelSender.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/PanelSender.cpp$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/PanelSender.cpp$(DependSuffix): PanelSender.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/PanelSender.cpp$(ObjectSuffix) -MF$(IntermediateDirectory)/PanelSender.cpp$(DependSuffix) -MM PanelSender.cpp

$(IntermediateDirectory)/PanelSender.cpp$(PreprocessSuffix): PanelSender.cpp
	$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/PanelSender.cpp$(PreprocessSuffix) PanelSender.cpp

$(IntermediateDirectory)/Processor.cpp$(ObjectSuffix): Processor.cpp $(IntermediateDirectory)/Processor.cpp$(DependSuffix)
	$(CXX) $(IncludePCH) $(SourceSwitch) "/home/avmd/Documents/Work/Bulgaria/Processor/Processor.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/Processor.cpp$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/Processor.cpp$(DependSuffix): Processor.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/Processor.cpp$(ObjectSuffix) -MF$(IntermediateDirectory)/Processor.cpp$(DependSuffix) -MM Processor.cpp

$(IntermediateDirectory)/Processor.cpp$(PreprocessSuffix): Processor.cpp
	$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/Processor.cpp$(PreprocessSuffix) Processor.cpp

$(IntermediateDirectory)/SocketReceiver.cpp$(ObjectSuffix): SocketReceiver.cpp $(IntermediateDirectory)/SocketReceiver.cpp$(DependSuffix)
	$(CXX) $(IncludePCH) $(SourceSwitch) "/home/avmd/Documents/Work/Bulgaria/Processor/SocketReceiver.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/SocketReceiver.cpp$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/SocketReceiver.cpp$(DependSuffix): SocketReceiver.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/SocketReceiver.cpp$(ObjectSuffix) -MF$(IntermediateDirectory)/SocketReceiver.cpp$(DependSuffix) -MM SocketReceiver.cpp

$(IntermediateDirectory)/SocketReceiver.cpp$(PreprocessSuffix): SocketReceiver.cpp
	$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/SocketReceiver.cpp$(PreprocessSuffix) SocketReceiver.cpp

$(IntermediateDirectory)/SocketSender.cpp$(ObjectSuffix): SocketSender.cpp $(IntermediateDirectory)/SocketSender.cpp$(DependSuffix)
	$(CXX) $(IncludePCH) $(SourceSwitch) "/home/avmd/Documents/Work/Bulgaria/Processor/SocketSender.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/SocketSender.cpp$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/SocketSender.cpp$(DependSuffix): SocketSender.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/SocketSender.cpp$(ObjectSuffix) -MF$(IntermediateDirectory)/SocketSender.cpp$(DependSuffix) -MM SocketSender.cpp

$(IntermediateDirectory)/SocketSender.cpp$(PreprocessSuffix): SocketSender.cpp
	$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/SocketSender.cpp$(PreprocessSuffix) SocketSender.cpp

$(IntermediateDirectory)/SerialSender.cpp$(ObjectSuffix): SerialSender.cpp $(IntermediateDirectory)/SerialSender.cpp$(DependSuffix)
	$(CXX) $(IncludePCH) $(SourceSwitch) "/home/avmd/Documents/Work/Bulgaria/Processor/SerialSender.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/SerialSender.cpp$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/SerialSender.cpp$(DependSuffix): SerialSender.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/SerialSender.cpp$(ObjectSuffix) -MF$(IntermediateDirectory)/SerialSender.cpp$(DependSuffix) -MM SerialSender.cpp

$(IntermediateDirectory)/SerialSender.cpp$(PreprocessSuffix): SerialSender.cpp
	$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/SerialSender.cpp$(PreprocessSuffix) SerialSender.cpp


-include $(IntermediateDirectory)/*$(DependSuffix)
##
## Clean
##
clean:
	$(RM) -r ./Debug/


