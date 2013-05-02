// TODO: make target MCU dependent
#ifdef LIBPERIPHA
#include <arm/cortex-m/stm32/gpio.h>
#include <arm/cortex-m/stm32/rcc.h>
#else
#include <stm32f10x.h>
#endif
