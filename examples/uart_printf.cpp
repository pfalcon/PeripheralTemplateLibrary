#include <gpio.hpp>
#include <cpu.hpp>
#include <board.hpp>
#include <timer.hpp>
#include <uart.hpp>
#include <console.hpp>

typedef UART<board::freq, 9600, board::pin_uart_tx, board::pin_uart_rx, timer> uart;
//typedef UART<1 MHZ, 9600, USCI> uart;
typedef Console<uart> con;

int main()
{
    cpu::init(cpu::DEFAULT);
    timer::free_run();
    uart::init();

    while (true) {
        uint8_t b = uart::read();
        con::printf("%d %u %x\n", 50000u, 50000u, 0xaa55u);
        con::printf("%ld %lx\n", 123456789l, 0xaa551234l);
    }
}
