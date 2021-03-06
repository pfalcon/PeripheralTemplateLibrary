#include <gpio.hpp>
#include <cpu.hpp>
#include <board.hpp>
#include <timer.hpp>
#include <uart.hpp>

#include HW_CONFIG

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
