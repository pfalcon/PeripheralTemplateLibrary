#ifdef __MSP430__
#include <gpio_msp430.hpp>
#elif defined( __AVR__)
#include <gpio_avr.hpp>
#else
#error Unknown platform in gpio.hpp
#endif
