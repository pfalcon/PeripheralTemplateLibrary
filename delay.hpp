#if defined(__MSP430__)
#define delay(x) __delay_cycles(x)
#else
#error Unknown platform in delay.hpp
#endif
