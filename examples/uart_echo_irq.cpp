#include <gpio.hpp>
#include <cpu.hpp>
#include <board.hpp>
#include <uart.hpp>

#include HW_CONFIG

namespace PTL {

template <>
void uart::uart_rx_irq_handler()
{
    uart::write_async(uart::read_async());
    board::LED::toggle();
}

}

int main()
{
    cpu::init(cpu::DEFAULT);
    board::LED::output();
    board::LED::low();
    hwuart::init();
    hwuart::enable_rx_irq();
    cpu::enable_irq();

    while (true);
}
