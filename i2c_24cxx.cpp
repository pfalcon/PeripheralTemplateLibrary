#include <cpu.hpp>
#include <board.hpp>
#include <gpio.hpp>
#include <i2c.hpp>
#include <timer.hpp>
#include <uart.hpp>
#include <console.hpp>


typedef UART<Pin<P1, Bit1>, Pin<P1, Bit2>, timer, 1 MHZ / 9600> uart;
typedef I2C< Pin<P1, Bit4>, Pin<P1, Bit5>, timer, 10 > i2c;

int main()
{
    cpu::init(cpu::DEFAULT);
    timer::free_run();
    uart::init();
    i2c::init();
    while (1) {
        uart::read();
        i2c::start();
        bool ack1 = i2c::write(0xa0);
        bool ack2 = i2c::write(0);
        bool ack3 = i2c::write(0x66);
        i2c::stop();
        Console<uart>::puthex8(ack1);
        Console<uart>::puthex8(ack2);
        Console<uart>::puthex8(ack3);
        Console<uart>::newline();

        i2c::start();
        ack1 = i2c::write(0xa0);
        ack2 = i2c::write(0);
        i2c::restart();
        ack3 = i2c::write(0xa1);
        uint8_t b1 = i2c::read(true);
        uint8_t b2 = i2c::read(false);
        i2c::stop();

        Console<uart>::puthex8(ack3);
        Console<uart>::newline();
        Console<uart>::puthex8(b1);
        Console<uart>::puthex8(b2);
        Console<uart>::newline();
    }
}
