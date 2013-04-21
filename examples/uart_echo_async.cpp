#include <gpio.hpp>
#include <cpu.hpp>
#include <board.hpp>
#include <uart.hpp>

typedef UART<1 MHZ, 9600, USCI> uart;

int main()
{
    cpu::init(cpu::DEFAULT);
    uart::init();

    while (true) {
        if (uart::read_ready()) {
            uint8_t b = uart::read_async();
            // This is known to be short
            while (!uart::write_ready());
            uart::write_async(b);
        }
    }
}
