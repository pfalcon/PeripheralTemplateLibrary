#include <gpio.hpp>
#include <cpu.hpp>
#include <board.hpp>
#include <timer.hpp>


typedef timer delayer;

int main()
{
    cpu::init(cpu::DEFAULT);
    board::LED::port::enable();
    board::LED::output();
    timer::free_run();
    while (true) {
        board::LED::high();
        delayer::delay(100000U);
        board::LED::low();
        delayer::delay(100000U);
    }
}
