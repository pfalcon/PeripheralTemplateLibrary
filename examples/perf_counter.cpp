#include <cpu.hpp>
#include <board.hpp>
#include <timer.hpp>
#include <uart.hpp>
#include <console.hpp>
#include <delay_static.hpp>
#include <rtos/perf_counter.hpp>
#include <rtos/perf_counter_acu.hpp>

#include HW_CONFIG

using namespace PTL;

typedef Console<uart> con;

PerfCounter<timer> counter;
PerfCounterAcu<timer> accu;


int main()
{
    cpu::init(cpu::DEFAULT);
    timer::free_run();
    uart::init();

    while (1) {
        uart::read();

        counter.start();
        counter.stop();
        con::putstr("Measuring 0 commands: ");
        con::putdec(counter.value());
        con::newline();

        counter.start();
        asm("nop");
        counter.stop();
        con::putstr("Measuring NOP: ");
        con::putdec(counter.value());
        con::newline();

        counter.start();
        StaticDelay::delay(1000);
        counter.stop();
        con::putstr("Measuring StaticDelay::delay(1000): ");
        con::putdec(counter.value());
        con::newline();

        accu.start();
        StaticDelay::delay(10000);
        accu.update();
        con::putstr("PerfAcu after delay(10000): ");
        con::putdec(accu.value());
        con::newline();
    }
}
