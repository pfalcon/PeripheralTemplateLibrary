#include <gpio.hpp>
#include <cpu.hpp>
#include <board.hpp>
#include <timer.hpp>

using namespace PTL;

namespace PTL {

template <>
void timer::irq_handler()
{
    // Ack IRQ
    timer::irq_status();
    board::LED::toggle();
}

}

int main()
{
    cpu::init(cpu::DEFAULT);
    board::LED::port::enable();
    board::LED::output();
    board::LED::high();
    timer::free_run();
    timer::enable_irq();
    cpu::enable_irq();
    while (true);
}
