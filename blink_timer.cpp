#include <gpio.hpp>
#include <cpu.hpp>
#include <board.hpp>
#include <timer.hpp>


typedef timer delayer;
typedef board::LED led;

int main()
{
    cpu::init(cpu::DEFAULT);
    led::port::enable();
    led::output();
    timer::free_run();
    while (true) {
        led::high();
        delayer::delay(1000000U);
        led::low();
        delayer::delay(1000000U);
    }
}
