#include <delay_base.hpp>
#if defined(__MSP430__)
#include <delay_msp430.hpp>
#elif defined(__AVR__)
#include <delay_avr.hpp>
#else
#error Unknown platform in delay.hpp
#endif
