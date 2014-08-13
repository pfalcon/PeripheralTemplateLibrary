#include <gpio.hpp>
#include <cpu.hpp>
#include <board.hpp>
#include <delay.hpp>
#include "blink_c_api.h"

using namespace PTL;

typedef Delay delayer;

void led_high()
{
    board::LED::high();
}

void led_low()
{
    board::LED::low();
}

void delay(uint32_t val)
{
    delayer::delay(val);
}

void init()
{
    cpu::init(cpu::DEFAULT);
    board::LED::port::enable();
    board::LED::output();
}
