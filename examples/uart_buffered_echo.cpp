#include <gpio.hpp>
#include <cpu.hpp>
#include <board.hpp>
#include <timer.hpp>
#include <uart.hpp>
#include <rtos/buffered_uart.hpp>

#include HW_CONFIG

BufferedUart<uart, 16, 16> buart;

int main()
{
    cpu::init(cpu::DEFAULT);
    timer::free_run();
    buart::init();

    while (true) {
        uint8_t b = buart::read();
        buart::write(b);
    }
}
