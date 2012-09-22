TARGET = msp430

ifeq ($(TARGET), avr)
MCU = atmega168
endif
ifeq ($(TARGET), msp430)
MCU = msp430g2553
endif

CROSS_COMPILE = $(TARGET)-
CC = $(CROSS_COMPILE)gcc
CXX = $(CROSS_COMPILE)g++
OBJDUMP = $(CROSS_COMPILE)objdump
OBJCOPY = $(CROSS_COMPILE)objcopy

INCLUDE = -I.
CFLAGS = $(INCLUDE) -mmcu=$(MCU) -O -g
CXXFLAGS = $(CFLAGS)

$(TARGET)/blink: $(TARGET)/blink.o

$(TARGET)/blink.o: blink.cpp

$(TARGET)/%.o: %.cpp
	mkdir -p $(TARGET)
	$(CXX) $(CXXFLAGS) -c $^ -o $@

ifeq ($(TARGET), msp430)
flash-%: $(TARGET)/%
	mspdebug rf2500 "prog $^"
endif
ifeq ($(TARGET), avr)
$(TARGET)/%.hex: $(TARGET)/%
	$(OBJCOPY) -O ihex -R .eeprom $^ $@
	$(OBJCOPY) -j .eeprom --set-section-flags=.eeprom="alloc,load" --change-section-lma .eeprom=0 --no-change-warnings -O ihex $^ $^.eep || exit 0

flash-%: $(TARGET)/%.hex
	avrdude -p m328p -c arduino -P/dev/ttyUSB0 -b57600 -D -Uflash:w:$^
endif

disasm-%: $(TARGET)/%
	$(OBJDUMP) -dSt --demangle $^ >$^.disasm

clean:
	rm -f $(TARGET)/*.o
