include Makefile.rules

ALL = blink blink_dynamic blink_timer uart_echo spi i2c_24cxx 1wire adc

.PHONY: $(ALL)

all: $(ALL)

blink: $(TARGETDIR)/blink
blink_dynamic: $(TARGETDIR)/blink_dynamic
blink_timer: $(TARGETDIR)/blink_timer
uart_echo: $(TARGETDIR)/uart_echo
spi: $(TARGETDIR)/spi
i2c_24cxx: $(TARGETDIR)/i2c_24cxx
1wire: $(TARGETDIR)/1wire
adc: $(TARGETDIR)/adc

$(TARGETDIR)/blink: $(TARGETDIR)/blink.o
$(TARGETDIR)/blink.o: blink.cpp

$(TARGETDIR)/blink_dynamic: $(TARGETDIR)/blink_dynamic.o
$(TARGETDIR)/blink_dynamic.o: blink_dynamic.cpp

$(TARGETDIR)/blink_timer: $(TARGETDIR)/blink_timer.o
$(TARGETDIR)/blink_timer.o: blink_timer.cpp

$(TARGETDIR)/uart_echo: $(TARGETDIR)/uart_echo.o
$(TARGETDIR)/uart_echo.o: uart_echo.cpp

$(TARGETDIR)/spi: $(TARGETDIR)/spi.o
$(TARGETDIR)/spi.o: spi.cpp

$(TARGETDIR)/i2c_24cxx: $(TARGETDIR)/i2c_24cxx.o
$(TARGETDIR)/i2c_24cxx.o: i2c_24cxx.cpp

$(TARGETDIR)/1wire: $(TARGETDIR)/1wire.o
$(TARGETDIR)/1wire.o: 1wire.cpp

$(TARGETDIR)/adc: $(TARGETDIR)/adc.o
$(TARGETDIR)/adc.o: adc.cpp
