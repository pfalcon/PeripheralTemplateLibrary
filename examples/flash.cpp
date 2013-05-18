#include <gpio.hpp>
#include <cpu.hpp>
#include <board.hpp>
#include <timer.hpp>
#include <uart.hpp>
#include <console.hpp>
#include <flash.hpp>

using namespace PTL;

typedef UART<1 MHZ, 9600, Pin<P1, Bit2>, Pin<P1, Bit1>, timer> uart;
//typedef UART<1 MHZ, 9600, USCI> uart;
typedef Console<uart> con;

int main()
{
    cpu::init(cpu::DEFAULT);
    timer::free_run();
    uart::init();

    Flash::init();

    uart::read();

    con::putstr("Current value: ");
    con::puthex16(*(uint16_t*)FLASH_SEGMENT_D);
    con::newline();

    Flash::erase((uint16_t*)FLASH_SEGMENT_D);
    con::putstr("After erase: ");
    con::puthex16(*(uint16_t*)FLASH_SEGMENT_D);
    con::newline();

    con::putstr("After write: ");
    Flash::write16((uint16_t*)FLASH_SEGMENT_D, 0x1234);
    con::puthex16(*(uint16_t*)FLASH_SEGMENT_D);
    con::newline();
}
