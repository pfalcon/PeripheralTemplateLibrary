#include <cpu.hpp>
#include <board.hpp>
#include <gpio.hpp>
#include <delay_static.hpp>
#include <timer.hpp>
#include <uart.hpp>
#include <console.hpp>
#include <1wire.hpp>


typedef UART<Pin<P1, Bit1>, Pin<P1, Bit2>, timer, 8 MHZ / 9600> uart;
typedef OneWire< Pin<P1, Bit5>, timer > onewire;
typedef Console<uart> con;

uint8_t crc8(uint8_t *buf, int len);

void read_scratchpad(uint8_t *buf)
{
    bool res = onewire::reset();
    Console<uart>::puthex8(res);
    Console<uart>::newline();

    onewire::write(0xcc);
    onewire::write(0xbe);
    onewire::read_block(buf, 9);
    con::puthex8(buf, 9);
    Console<uart>::newline();

    uint8_t crc = crc8(buf, 9);
    Console<uart>::puthex8(crc);
    Console<uart>::newline();
}

int main()
{
    cpu::init(cpu::FREQ_8MHZ);
    timer::free_run();
    uart::init();
    onewire::init();

    while (1) {
        uint8_t buf[9];
        uart::read();

        bool res = onewire::reset();
        Console<uart>::puthex8(res);
        onewire::write(0xcc);
        onewire::write(0xb4);
        uint8_t b = onewire::read();
        Console<uart>::puthex8(b);
        Console<uart>::newline();

        onewire::reset();
        onewire::write(0x33);
        onewire::read_block(buf, 8);
        con::puthex8(buf, 8);
        con::newline();
        con::puthex8(crc8(buf, 8));
        con::newline();
        con::newline();

        read_scratchpad(buf);

        onewire::reset();
        onewire::write(0xcc);
        onewire::write(0x44);
        onewire::bus_power();
        delay_ms<8 MHZ, 800>();

        read_scratchpad(buf);
    }
}

// Based on http://en.wikipedia.org/wiki/Computation_of_CRC#Parallel_computation_without_table
uint8_t crc8(uint8_t *buf, int len)
{
    uint8_t c = 0;
    for (int i = len; len; len--) {
        uint8_t d = *buf++, e, f, r;
        e = c ^ d;
        f = e ^ (e << 3) ^ (e << 4) ^ (e << 6);
        r = f ^ (f >> 4) ^ (f >> 5);
        c = r;
    }
    return c;
}
