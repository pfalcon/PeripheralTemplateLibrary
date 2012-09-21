#include <gpio.hpp>
#include <delay.hpp>
#include <cpu.hpp>
#include <board.hpp>


int main()
{
    cpu::init(cpu::DEFAULT);
    board::LED::output();
    while (true) {
        board::LED::high();
        delay(50000);
        board::LED::low();
        delay(50000);
    }
}
