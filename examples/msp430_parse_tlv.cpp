#include <cpu.hpp>
#include <board.hpp>
#include <gpio.hpp>
#include <timer.hpp>
#include <uart.hpp>
#include <console.hpp>
#include <delay_static.hpp>

#ifndef TAG_EMPTY
#define TAG_EMPTY 0xfe
#define TAG_DCO_30 0x01
#define TAG_ADC12_1 0x08
#define TAG_ADC10_1 0x10
#endif

typedef UART<1 MHZ, 9600, Pin<P1, Bit2>, Pin<P1, Bit1>, timer> uart;
typedef Console<uart> con;


void show_word(const char *descr, uint8_t *p)
{
    con::putc(' ');
    con::putstr(descr);
    con::putc(' ');
    con::puthex16(*(uint16_t*)p);
    con::newline();
}

int main()
{
    cpu::init(cpu::DEFAULT);
    timer::free_run();
    uart::init();

    while (1) {
        uart::read();
        for (uint8_t *p = (uint8_t*)0x10c2; p < (uint8_t*)0x1100;) {
            uint8_t tag = *p++;
            switch (tag) {
            case TAG_EMPTY:
                con::putstr("TAG_EMPTY");
                break;
            case TAG_DCO_30:
                con::putstr("TAG_DCO_30");
                break;
            case TAG_ADC12_1:
                con::putstr("TAG_ADC12_1");
                break;
            case TAG_ADC10_1:
                con::putstr("TAG_ADC10_1");
                break;
            }
            uint8_t len = *p++;
            con::putc(' ');
            con::puthex8(len);
            con::newline();

            switch (tag) {
            case TAG_ADC10_1:
                show_word("CAL_ADC_GAIN_FACTOR", p); p += 2;
                show_word("CAL_ADC_OFFSET", p); p += 2;
                show_word("CAL_ADC_15VREF_FACTOR", p); p += 2;
                show_word("CAL_ADC_15T30", p); p += 2;
                show_word("CAL_ADC_15T85", p); p += 2;
                show_word("CAL_ADC_25VREF_FACTOR", p); p += 2;
                show_word("CAL_ADC_25T30", p); p += 2;
                show_word("CAL_ADC_25T85", p); p += 2;
                break;
            default:
                p += len;
                break;
            }
        }
    }
}
