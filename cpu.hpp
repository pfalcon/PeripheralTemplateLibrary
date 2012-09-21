#if defined(__MSP430__)
#include <cpu_msp430.hpp>
#elif defined(__AVR__)
#include <cpu_avr.hpp>
#else
#error Unknown platform in cpu.hpp
#endif
