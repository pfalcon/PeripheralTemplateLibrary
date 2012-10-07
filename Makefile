include Makefile.rules

ALL = blink blink_timer uart_echo spi i2c_24cxx 1wire adc

.PHONY: $(ALL)

all: $(ALL)

blink: $(TARGET)/blink
blink_timer: $(TARGET)/blink_timer
uart_echo: $(TARGET)/uart_echo
spi: $(TARGET)/spi
i2c_24cxx: $(TARGET)/i2c_24cxx
1wire: $(TARGET)/1wire
adc: $(TARGET)/adc

$(TARGET)/blink: $(TARGET)/blink.o
$(TARGET)/blink.o: blink.cpp

$(TARGET)/blink_timer: $(TARGET)/blink_timer.o
$(TARGET)/blink_timer.o: blink_timer.cpp

$(TARGET)/uart_echo: $(TARGET)/uart_echo.o
$(TARGET)/uart_echo.o: uart_echo.cpp

$(TARGET)/spi: $(TARGET)/spi.o
$(TARGET)/spi.o: spi.cpp

$(TARGET)/i2c_24cxx: $(TARGET)/i2c_24cxx.o
$(TARGET)/i2c_24cxx.o: i2c_24cxx.cpp

$(TARGET)/1wire: $(TARGET)/1wire.o
$(TARGET)/1wire.o: 1wire.cpp

$(TARGET)/adc: $(TARGET)/adc.o
$(TARGET)/adc.o: adc.cpp
