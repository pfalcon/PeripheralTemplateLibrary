#include <gpio.hpp>
#include <cpu.hpp>
#include <board.hpp>
#include <timer.hpp>
#include <irq_dispatch.hpp>

#include HW_CONFIG

class mytimer : public timer
{
public:
    static void irq_reset()
    {
        board::LED::toggle();
    }
};

IRQ_DISPATCH(mytimer);

int main()
{
    cpu::init(cpu::DEFAULT);
    board::LED::port::enable();
    board::LED::output();
    mytimer::free_run();
    mytimer::enable_irq();
    cpu::enable_irq();
    while (true);
}
