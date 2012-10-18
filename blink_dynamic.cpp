#include <gpio.hpp>
#include <cpu.hpp>
#include <board.hpp>
#include <delay.hpp>


int main()
{
    cpu::init(cpu::DEFAULT);
    board::LED::port::enable();
    board::LED::output();
    while (true) {
        board::LED::high();
        Delay::delay(3000000);
        board::LED::low();
        Delay::delay(3000000);
    }
}
