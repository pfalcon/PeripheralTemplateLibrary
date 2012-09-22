#if defined(__MSP430__)
#include <cpu_msp430.hpp>
#elif defined(__AVR__)
#include <cpu_avr.hpp>
#elif defined(__STM32__)
#include <cpu_stm32.hpp>
#else
#error Unknown platform in cpu.hpp
#endif
