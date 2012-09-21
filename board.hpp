// TODO: Selecting board based on CPU is very rough
#if defined(__MSP430__)
#include <board_launchpad.hpp>
#elif defined(__AVR__)
#include <board_arduino.hpp>
#else
#error Unknown platform in cpu.hpp
#endif
