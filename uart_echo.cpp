#include <gpio.hpp>
#include <cpu.hpp>
#include <board.hpp>
#include <timer.hpp>
#include <uart.hpp>

typedef UART<Pin<P1, Bit1>, Pin<P1, Bit2>, timer, 1 MHZ / 9600> uart;

int main()
{
    cpu::init(cpu::DEFAULT);
    timer::free_run();
    uart::init();

    while (true) {
        uint8_t b = uart::read();
        uart::write(b);
    }
}
