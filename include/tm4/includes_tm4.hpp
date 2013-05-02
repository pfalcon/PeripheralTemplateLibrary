// TODO: make target MCU dependent
#ifdef LIBPERIPHA
#include <arm/cortex-m/lm4/scr.h>
#include <arm/cortex-m/lm4/gpio.h>
#include <arm/cortex-m/lm4/uart.h>
#else
#error Untested
#endif
