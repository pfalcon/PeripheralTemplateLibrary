#include <cpu.hpp>
#include <board.hpp>
#include <gpio.hpp>
#include <spi.hpp>
#include <timer.hpp>
#include <uart.hpp>
#include <console.hpp>


typedef UART<Pin<P1, Bit1>, Pin<P1, Bit2>, timer, 1 MHZ / 9600> uart;
typedef SPI< Pin<P1, Bit5>, Pin<P1, Bit6>, Pin<P1, Bit7> > spi;

typedef Pin<P2, Bit1> CS;

int main()
{
    cpu::init(cpu::DEFAULT);
    timer::free_run();
    uart::init();
    spi::init();
    CS::output();
    CS::high();
    while (1) {
        uart::read();
        CS::low();
        uint8_t b = spi::transfer(0xff);
        CS::high();
        Console<uart>::puthex8(b);
        Console<uart>::newline();
    }
}
