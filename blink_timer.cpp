#include <gpio.hpp>
#include <delay.hpp>
#include <cpu.hpp>
#include <board.hpp>
#include <timer.hpp>
#include <delay_new.hpp>


int main()
{
    cpu::init(cpu::DEFAULT);
    board::LED::port::enable();
    board::LED::output();
    timer::free_run();
    while (true) {
        board::LED::high();
        timer::delay(65535);
        board::LED::low();
        timer::delay(65535);
    }
}
