#include <gpio.hpp>
#include <cpu.hpp>
#include <board.hpp>
#include <timer.hpp>
#include <rtos/ticks.hpp>

using namespace PTL;

typedef Ticks<> delayer;
typedef board::LED led;

namespace PTL {
// For Ticks to actually work, we must route hardware timer
// interrupts to it
IRQ_DISPATCH(timer, delayer::Irqs);
}

int main()
{
    cpu::init(cpu::DEFAULT);
    led::port::enable();
    led::output();
    timer::free_run();
    timer::enable_irq();
    cpu::enable_irq();
    while (true) {
        led::low();
        delayer::delay(10);
        led::high();
        delayer::delay(10);
    }
}
