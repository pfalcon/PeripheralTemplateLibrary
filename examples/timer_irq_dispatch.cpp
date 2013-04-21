#include <gpio.hpp>
#include <cpu.hpp>
#include <board.hpp>
#include <timer.hpp>
#include <timer_irq_dispatch.hpp>

struct TimerIrqs : public TimerIrqsBase {
    static void overflow()
    {
        board::LED::toggle();
    }
};

IRQ_DISPATCH(timer, TimerIrqs);

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
