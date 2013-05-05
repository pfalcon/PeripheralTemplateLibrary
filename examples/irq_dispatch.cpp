#include <gpio.hpp>
#include <cpu.hpp>
#include <board.hpp>
#include <timer.hpp>
#include <uart.hpp>
#include <spi.hpp>
#include <msp430/irq_dispatch_msp430.hpp>

#include HW_CONFIG

class mytimer : public timer
{
public:
    static void irq_reset()
    {
        board::LED::toggle();
    }
};

class myuart : public uart
{
public:
    static void irq_rx()
    {
        board::LED::toggle();
    }
};

class myspi : public spi
{
public:
    static void irq_rx()
    {
        board::LED2::toggle();
    }
};

// Explicit instantiation of IRQ dispatcher class
template class IrqDispatch<mytimer, myuart, myspi>;


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
