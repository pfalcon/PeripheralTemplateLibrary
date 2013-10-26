#include <delay_static.hpp>
#include <gpio.hpp>
#include <cpu.hpp>
#include <board.hpp>
#include <timer.hpp>
#include <uart.hpp>
#include <rtos/buffered_uart.hpp>
#include <irq_dispatch.hpp>

#include HW_CONFIG

typedef BufferedUart<hwuart, 16, 16> buart;

IRQ_DISPATCH(buart::uart_handlers);

int main()
{
    cpu::init(cpu::DEFAULT);
    board::LED::output();
    board::LED::low();
    buart::init();
    cpu::enable_irq();

    while (true) {
        // We have time to process only 3 incoming chars, ...
        for (int i = 0; i < 3; i++) {
            uint8_t b = buart::read();
            board::LED::toggle();
            buart::write(b);
        }
        // ..., and then we're busy with very important task
        // The whole idea is that even if we don't process incoming
        // chars regularly, they are not lost, but buffered in
        // background.
        StaticDelay::delay(500000U);
    }
}
