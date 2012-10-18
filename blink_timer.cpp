#include <gpio.hpp>
#include <cpu.hpp>
#include <board.hpp>
#include <timer.hpp>


int main()
{
    cpu::init(cpu::DEFAULT);
    board::LED::port::enable();
    board::LED::output();
    timer::free_run();
    while (true) {
        board::LED::high();
        timer::delay(200000);
        board::LED::low();
        timer::delay(200000);
    }
}
