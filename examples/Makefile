PTL_PATH = ..
include $(PTL_PATH)/Makefile.rules

ALL = blink blink_static blink_dynamic blink_timer blink_ticks \
      blink_sleep blink_bus blink_dynapin blink_c \
      uart_echo uart_echo_irq uart_echo_async uart_echo_buffered \
      uart_printf \
      spi i2c_24cxx 1wire adc \
      timer_irq timer_irq_dispatch irq_dispatch irq_dispatch_simple \
      flash \
      perf_counter lcd lcd_nokia \
      msp430_parse_tlv

.PHONY: $(ALL)

all: $(ALL)

blink: $(TARGETDIR)/blink
blink_static: $(TARGETDIR)/blink_static
blink_dynamic: $(TARGETDIR)/blink_dynamic
blink_timer: $(TARGETDIR)/blink_timer
blink_ticks: $(TARGETDIR)/blink_ticks
blink_sleep: $(TARGETDIR)/blink_sleep
blink_bus: $(TARGETDIR)/blink_bus
blink_dynapin: $(TARGETDIR)/blink_dynapin
blink_c: $(TARGETDIR)/blink_c
uart_echo: $(TARGETDIR)/uart_echo
uart_echo_irq: $(TARGETDIR)/uart_echo_irq
uart_echo_async: $(TARGETDIR)/uart_echo_async
uart_echo_buffered: $(TARGETDIR)/uart_echo_buffered
uart_printf: $(TARGETDIR)/uart_printf
spi: $(TARGETDIR)/spi
i2c_24cxx: $(TARGETDIR)/i2c_24cxx
1wire: $(TARGETDIR)/1wire
adc: $(TARGETDIR)/adc
timer_irq: $(TARGETDIR)/timer_irq
timer_irq_dispatch: $(TARGETDIR)/timer_irq_dispatch
irq_dispatch_simple: $(TARGETDIR)/irq_dispatch_simple
irq_dispatch: $(TARGETDIR)/irq_dispatch
flash: $(TARGETDIR)/flash
perf_counter: $(TARGETDIR)/perf_counter
lcd: $(TARGETDIR)/lcd
lcd_nokia: $(TARGETDIR)/lcd_nokia
msp430_parse_tlv: $(TARGETDIR)/msp430_parse_tlv

$(TARGETDIR)/blink: $(TARGETDIR)/blink.o
$(TARGETDIR)/blink.o: blink.cpp

$(TARGETDIR)/blink_static: $(TARGETDIR)/blink_static.o
$(TARGETDIR)/blink_static.o: blink_static.cpp

$(TARGETDIR)/blink_dynamic: $(TARGETDIR)/blink_dynamic.o
$(TARGETDIR)/blink_dynamic.o: blink_dynamic.cpp

$(TARGETDIR)/blink_timer: $(TARGETDIR)/blink_timer.o
$(TARGETDIR)/blink_timer.o: blink_timer.cpp

$(TARGETDIR)/blink_ticks: $(TARGETDIR)/blink_ticks.o
$(TARGETDIR)/blink_ticks.o: blink_ticks.cpp

$(TARGETDIR)/blink_bus: $(TARGETDIR)/blink_bus.o
$(TARGETDIR)/blink_bus.o: blink_bus.cpp

$(TARGETDIR)/blink_c: $(TARGETDIR)/blink_c.o $(TARGETDIR)/blink_c_api.o

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

$(TARGETDIR)/lcd: $(TARGETDIR)/lcd.o
$(TARGETDIR)/lcd.o: lcd.cpp

$(TARGETDIR)/irq_dispatch: $(TARGETDIR)/irq_dispatch.o
$(TARGETDIR)/irq_dispatch_simple: $(TARGETDIR)/irq_dispatch_simple.o
