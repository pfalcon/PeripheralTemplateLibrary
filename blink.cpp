#include <gpio.hpp>
#include <cpu.hpp>
#include <board.hpp>
#include <delay_static.hpp>


int main()
{
    cpu::init(cpu::DEFAULT);
    board::LED::port::enable();
    board::LED::output();
    while (true) {
        board::LED::high();
        delay_ms<board::freq, 1000>();
        board::LED::low();
        delay_ms<board::freq, 1000>();
    }
}
