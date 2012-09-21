TARGET=msp430
CROSS_COMPILE = $(TARGET)-
CC = $(CROSS_COMPILE)gcc
CXX = $(CROSS_COMPILE)g++
OBJDUMP = $(CROSS_COMPILE)objdump

INCLUDE = -I.
CFLAGS = $(INCLUDE) -O
CXXFLAGS = $(CFLAGS)

blink: blink.o

blink.o: blink.cpp

flash-%: %
	mspdebug rf2500 "prog $^"

disasm-%: %
	$(OBJDUMP) -dSt --demangle $^ >$^.disasm

clean:
	rm -f *.o
