// TODO: make target MCU dependent
#ifdef LIBPERIPHA
#include <cortex-m/stm32/gpio.h>
#include <cortex-m/stm32/rcc.h>
#else
#include <stm32f10x.h>
#endif
