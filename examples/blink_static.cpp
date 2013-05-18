#include <gpio.hpp>
#include <cpu.hpp>
#include <board.hpp>
#include <delay_static.hpp>

using namespace PTL;

typedef StaticDelay delayer;
typedef board::LED led;


int main()
{
    cpu::init(cpu::DEFAULT);
    led::port::enable();
    led::output();
    while (true) {
        led::high();
        delayer::delay(1000000U);
        led::low();
        delayer::delay(1000000U);
    }
}
