#include <gpio.hpp>
#include <cpu.hpp>
#include <board.hpp>
#include <timer.hpp>
#include <uart.hpp>

typedef UART<board::freq, 9600, board::pin_uart_tx, board::pin_uart_rx, timer> uart;
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
