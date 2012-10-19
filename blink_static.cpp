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
        StaticDelay::delay(100000U);
        board::LED::low();
        StaticDelay::delay(100000U);
    }
}
