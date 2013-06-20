#include <gpio.hpp>
#include <cpu.hpp>
#include <board.hpp>
#include <timer.hpp>
#include <uart.hpp>
#include <spi.hpp>
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

IRQ_DISPATCH(mytimer, myuart, myspi);

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
