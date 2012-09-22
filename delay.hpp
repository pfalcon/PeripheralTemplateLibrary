#include <delay_base.hpp>
#if defined(__MSP430__)
#include <delay_msp430.hpp>
#elif defined(__AVR__)
#include <delay_avr.hpp>
#elif defined(__STM32__)
#include <delay_stm32.hpp>
#else
#error Unknown platform in delay.hpp
#endif
