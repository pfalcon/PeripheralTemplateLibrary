#include <cpu.hpp>
#include <board.hpp>
#include <timer.hpp>
#include <uart.hpp>
#include <console.hpp>
#include <delay_static.hpp>
#include <perf_counter.hpp>


typedef UART<1 MHZ, 9600, Pin<P1, Bit2>, Pin<P1, Bit1>, timer> uart;
typedef Console<uart> con;

int main()
{
    cpu::init(cpu::DEFAULT);
    timer::free_run();
    uart::init();

    while (1) {
        uart::read();

        PerfCounter<timer> counter;

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
    }
}
