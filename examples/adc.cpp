#include <cpu.hpp>
#include <board.hpp>
#include <gpio.hpp>
#include <timer.hpp>
#include <uart.hpp>
#include <console.hpp>
#include <adc.hpp>

using namespace PTL;

typedef UART<1 MHZ, 9600, Pin<P1, Bit2>, Pin<P1, Bit1>, timer> uart;
typedef Console<uart> con;
typedef ADC adc;

int main()
{
    cpu::init(cpu::DEFAULT);
    timer::free_run();
    uart::init();
    adc::unlock();
    adc::config<ADCDefaultConfig>();
    while (1) {
        uart::read();
        adc::width value = adc::easy_sample(adc::VCC_HALF);
        con::putdec(value);
        con::newline();
    }
}
