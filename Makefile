NAME       = NPGTOS
VERSION    = 0.0.1
MAINTAINER = $(USER)
OS         = $(shell uname -s)
PROC       = $(shell uname -m | tr _ -)

INSTALL_DIR= .
#INSTALL_DIR = $(HOME)

#DEFINES:=  -D_SNAFU -D_SNAFUBAR
DEFINES= -D_ISOC99_SOURCE -D_GNU_SOURCE -D_WTF  #-D_MPI

LIBS:= #-lm -lstdc++

#SRC_DIR:= ./src
#INCLUDES:= -I$(SRC_DIR) -I/usr/include/gdal -I$(SRC_DIR)/ConstsAstro -I$(SRC_DIR)/Currents -I$(SRC_DIR)/Geo -I$(SRC_DIR)/IO
#INCLUDES:= $(INCLUDES) -I$(SRC_DIR)/OceanicGridPoints -I$(SRC_DIR)/Utils -I$(SRC_DIR)/WaterLevels

#--- Use 
#ifeq ($(OS),Linux)
ifeq ($(OS),CYGWIN_NT-10.0)

  CC = g++

  #LD_FLAGS = -Bdynamic -static-intel
  LD_FLAGS:= -lm -lstdc++

  OPT_FLAGS = -O2 -finline-functions -fomit-frame-pointer -funroll-loops 
  #OPT_FLAGS:=

  CC_FLAGS:= -std=c++11 $(OPT_FLAGS) #-g3 #-fopenmp 

  LIBS:= $(LIBS) 

  #ifeq ($(PROC),x86-64)
  #   CC_FLAGS   = $(CC_FLAGS) -m64
  #endif

else #---- windoze stuff

  #CC=
  #LINK_EXEC := -lxlsmp -lpthread -lmass -lm -lxlf90

  #CC_FLAGS :=  -qsmp -O3 -qnohot -qinline -qcache=auto -qtune=auto -qarch=auto -qstrict 
                #-v -std=c99 -qlibmpi -qnosmp -O3 -qnohot -qstrict -Q -qcache=auto -qtune=auto -qarch=auto -qinline
                #-qnosmp  -qmaxmem=-1 -qalign=natural -qtbtable=full \
                #-qunroll -qlargepage -qstrict -qkeyword=restrict -qcache=auto -qtune=auto -qarch=auto 

  #INCLUDES := $(INCLUDES) #-I$(ARMNLIB)/include/AIX

  #LIBS := $(LIBS) $(LINK_EXEC) #-L/ssm/net/cmoe/base/20150217/aix-7.1-ppc7-64/lib  
  #-L/ssm/net/cmoe/eer/master/eerUtils_1.10.0-$(COMP_ARCH)_$(ORDENV_PLAT)/lib

  #LD_FLAGS := $(LD_FLAGS) -qlibmpi

endif

SFE:= cpp
IFE:= hpp

SRC_MDIR:= ./src
SRC_FILES0:= $(wildcard $(SRC_MDIR)/*.$(SFE))
OBJ_FILES0:= $(subst .cpp,.o, $(SRC_FILES0))

SRC_DIR1:= $(SRC_MDIR)/Core
SRC_FILES1:= $(wildcard $(SRC_DIR1)/*.$(SFE))
OBJ_FILES1:= $(subst .cpp,.o, $(SRC_FILES1))

SRC_DIR8:= $(SRC_MDIR)/System
SRC_FILES8:= $(wildcard $(SRC_DIR8)/*.$(SFE))
OBJ_FILES8:= $(subst .cpp,.o, $(SRC_FILES8))

SRC_DIR2:= $(SRC_MDIR)/EoS
SRC_FILES2:= $(wildcard $(SRC_DIR2)/*.$(SFE))
OBJ_FILES2:= $(subst .cpp,.o, $(SRC_FILES2))

SRC_DIR3:= $(SRC_MDIR)/Optimization
SRC_FILES3:= $(wildcard $(SRC_DIR3)/*.$(SFE))
OBJ_FILES3:= $(subst .cpp,.o, $(SRC_FILES3))

SRC_DIR4:= $(SRC_MDIR)/IO
SRC_FILES4:= $(wildcard $(SRC_DIR4)/*.$(SFE))
OBJ_FILES4:= $(subst .cpp,.o, $(SRC_FILES4))

SRC_DIR5:= $(SRC_MDIR)/Extensive
SRC_FILES5:= $(wildcard $(SRC_DIR5)/*.$(SFE))
OBJ_FILES5:= $(subst .cpp,.o, $(SRC_FILES5))

SRC_DIR6:= $(SRC_MDIR)/Intensive
SRC_FILES6:= $(wildcard $(SRC_DIR6)/*.$(SFE))
OBJ_FILES6:= $(subst .cpp,.o, $(SRC_FILES6))

SRC_DIR7:= $(SRC_MDIR)/Tensors
SRC_FILES7:= $(wildcard $(SRC_DIR7)/*.$(SFE))
OBJ_FILES7:= $(subst .cpp,.o, $(SRC_FILES7))

INC_FILES:= $(wildcard $(SRC_MDIR)/*.$(IFE)) $(wildcard $(SRC_DIR1)/*.$(IFE)) $(wildcard $(SRC_DIR2)/*.$(IFE)) $(wildcard $(SRC_DIR3)/*.$(IFE))
INC_FILES:= $(INC_FILES) $(wildcard $(SRC_DIR4)/*.$(IFE)) $(wildcard $(SRC_DIR5)/*.$(IFE)) $(wildcard $(SRC_DIR6)/*.$(IFE)) $(wildcard $(SRC_DIR7)/*.$(IFE))

SRC_FILES:= $(SRC_FILES6) $(SRC_FILES3) $(SRC_FILES4) $(SRC_FILES5) $(SRC_FILES7) $(SRC_FILES1) $(SRC_FILES8) $(SRC_FILES2) $(SRC_FILES0)
OBJ_FILES:= $(OBJ_FILES6) $(OBJ_FILES3) $(OBJ_FILES4) $(OBJ_FILES5) $(OBJ_FILES7) $(OBJ_FILES1) $(OBJ_FILES8) $(OBJ_FILES2) $(OBJ_FILES0) 

INCLUDES:=  -I$(SRC_MDIR) -I$(SRC_DIR1) -I$(SRC_DIR2) -I$(SRC_DIR3) -I$(SRC_DIR4)
INCLUDES:= $(INCLUDES) -I$(SRC_DIR5) -I$(SRC_DIR6) -I$(SRC_DIR7) -I$(SRC_DIR8) 

BIN_DIR:= ./bin

EXEC:= $(BIN_DIR)/$(NAME)-$(VERSION).xo

$(EXEC): $(OBJ_FILES)
	mkdir -p $(BIN_DIR) ; \
	$(CC) -o $@ $^ $(LD_FLAGS) $(LIBS) $(CC_FLAGS)

$(OBJ_FILES0): $(SRC_MDIR)/%.o : $(SRC_MDIR)/%.cpp  $(INC_FILES)
	$(CC) -c $< -o $@ $(CC_FLAGS) $(DEFINES) $(INCLUDES)

$(OBJ_FILES1): $(SRC_DIR1)/%.o : $(SRC_DIR1)/%.cpp  $(INC_FILES)
	$(CC) -c $< -o $@ $(CC_FLAGS) $(DEFINES) $(INCLUDES)

$(OBJ_FILES2): $(SRC_DIR2)/%.o : $(SRC_DIR2)/%.cpp  $(INC_FILES)
	$(CC) -c $< -o $@ $(CC_FLAGS) $(DEFINES) $(INCLUDES)

$(OBJ_FILES3): $(SRC_DIR3)/%.o : $(SRC_DIR3)/%.cpp  $(INC_FILES)
	$(CC) -c $< -o $@ $(CC_FLAGS) $(DEFINES) $(INCLUDES)

$(OBJ_FILES4): $(SRC_DIR4)/%.o : $(SRC_DIR4)/%.cpp  $(INC_FILES)
	$(CC) -c $< -o $@ $(CC_FLAGS) $(DEFINES) $(INCLUDES)

$(OBJ_FILES5): $(SRC_DIR5)/%.o : $(SRC_DIR5)/%.cpp  $(INC_FILES)
	$(CC) -c $< -o $@ $(CC_FLAGS) $(DEFINES) $(INCLUDES)

$(OBJ_FILES6): $(SRC_DIR6)/%.o : $(SRC_DIR6)/%.cpp  $(INC_FILES)
	$(CC) -c $< -o $@ $(CC_FLAGS) $(DEFINES) $(INCLUDES)

$(OBJ_FILES7): $(SRC_DIR7)/%.o : $(SRC_DIR7)/%.cpp  $(INC_FILES)
	$(CC) -c $< -o $@ $(CC_FLAGS) $(DEFINES) $(INCLUDES)

$(OBJ_FILES8): $(SRC_DIR8)/%.o : $(SRC_DIR8)/%.cpp  $(INC_FILES)
	$(CC) -c $< -o $@ $(CC_FLAGS) $(DEFINES) $(INCLUDES)

$(SRC_FILES): $(INC_FILES)

clear: clean
	rm -f $(EXEC)

clean:
	rm -f $(OBJ_FILES)
