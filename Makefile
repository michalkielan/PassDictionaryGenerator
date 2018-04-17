#############################################################
#  Setup variable section                                   #
#############################################################

# Compiler
COMPILER=g++

# C++ standard, ex. c++0x, c++11, c++14
CPP_STD= -std=c++14

# Optimization, ex. O3, O2
OPTIMIZATION=-O2

# target name
TARGET=pass_rand

# Linker flags variable
LDFLAGS=

# C, C++ flags
CFLAGS=

# source, include path
SRC=
INC=

# boost flags
BOOST= -lboost_system -lboost_program_options

#debug flag
DBG= -g

# sourcepaths
SRC_PATH=src/
INC_PATH=inc/

##############################################################
# Make file commands section                                 #
##############################################################

if[${CXX?}=""]; then CXX=$(COMPILER); fi;

CFLAGS+= -$(CPP_STD) 
CFLAGS+= -Wall 
CFLAGS+= $(DBG) 
CFLAGS+= $(OPTIMIZATION)

LDFLAGS+=$(BOOST)
LDFLAGS+=-lpthread

INC+=$(INC_PATH)
SRC+=$(shell ls $(SRC_PATH)*.cpp)

all:
	$(CXX) $(CFLAGS) -I $(INC) $(SRC) -o $(TARGET) $(LDFLAGS)
clean:
	rm -rf $(TARGET) *.o
	
	
	
	