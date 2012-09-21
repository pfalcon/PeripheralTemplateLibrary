#if defined(__MSP430__)
#define delay(x) __delay_cycles(x)
#elif defined(__AVR__)
#include <util/delay_basic.h>
#define delay(x) _delay_loop_2(x / 4)
#else
#error Unknown platform in delay.hpp
#endif
