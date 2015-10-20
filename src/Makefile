# ? allows override by user using env var
GCC ?= g++
CC_LIBS = -D__cplusplus=201103L -static-libgcc -static-libstdc++
INCLUDE = -I"./" -I"/usr/include/"
CC_FLAGS = -O0 -g -c  -std=c++11
LD_FLAGS = 
LIB_DIRS = 
LD_LIBS = 

default: argumentparser

%.o: %.cc argparser.h
	$(GCC) $(CC_LIBS) $(INCLUDE) $(CC_FLAGS) -o $@ $<

argumentparser: argparser.o example.o
	$(GCC) $(LD_FLAGS) $(LIB_DIRS) -o argumentparser $? $(LD_LIBS)

clean:
	rm argparser.o
	rm example.o
	rm argumentparser
