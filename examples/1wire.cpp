#include <cpu.hpp>
#include <board.hpp>
#include <gpio.hpp>
#include <delay_static.hpp>
#include <delay_time.hpp>
#include <timer.hpp>
#include <uart.hpp>
#include <console.hpp>
#include <1wire.hpp>

using namespace PTL;

#define READ_ROM 0x33
#define SKIP_ROM 0xCC
#define READ_POWER_SUPPLY 0xB4
#define CONVERT_T 0x44
#define READ_SCRATCHPAD 0xBE

typedef TimeDelay<8 MHZ, StaticDelay> delayer;
typedef UART<8 MHZ, 9600, Pin<P1, Bit2>, Pin<P1, Bit1>, timer> uart;
typedef OneWire< Pin<P1, Bit5>, timer > onewire;
typedef Console<uart> con;

uint8_t crc8(uint8_t *buf, int len);

void read_scratchpad(const char *msg, uint8_t *buf)
{
    bool res = onewire::reset();
    con::putstr("Presence: ");
    con::puthex8(res);
    con::newline();

    onewire::write(SKIP_ROM);
    onewire::write(READ_SCRATCHPAD);
    onewire::read_block(buf, 9);
    con::putstr(msg);
    con::puthex8(buf, 9);
    con::putc(' ');

    uint8_t crc = crc8(buf, 9);
    con::puthex8(crc);
    con::newline();
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
        con::putstr("Initial presence: ");
        con::puthex8(res);
        con::newline();

        onewire::write(SKIP_ROM);
        onewire::write(READ_POWER_SUPPLY);
        uint8_t b = onewire::read();
        con::putstr("Power status: ");
        con::puthex8(b);
        con::newline();

        onewire::reset();
        onewire::write(READ_ROM);
        onewire::read_block(buf, 8);
        con::putstr("Address: ");
        con::puthex8(buf, 8);
        con::putc(' ');
        con::puthex8(crc8(buf, 8));
        con::newline();

        read_scratchpad("Before measurement: ", buf);

        onewire::reset();
        onewire::write(SKIP_ROM);
        onewire::write(CONVERT_T);
        onewire::bus_power();
        delayer::delay_ms(800);

        read_scratchpad("After measurement: ", buf);
        con::newline();
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
