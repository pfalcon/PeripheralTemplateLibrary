#include <gpio.hpp>
#include <cpu.hpp>
#include <board.hpp>
#include <timer.hpp>
#include <uart.hpp>

typedef UART<1 MHZ, 9600, Pin<P1, Bit2>, Pin<P1, Bit1>, timer> uart;
//typedef UART<1 MHZ, 9600, USCI> uart;

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
