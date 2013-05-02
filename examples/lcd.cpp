#include <gpio.hpp>
#include <cpu.hpp>
#include <board.hpp>
#include <delay_static.hpp>
#include <delay_time.hpp>
#include <parallel_bus.hpp>
#include <console.hpp>
#include <device/hd44780.hpp>

#include HW_CONFIG

typedef TimeDelay<board::freq, StaticDelay> delayer;
typedef HD44780<delayer, hd44780_data, hd44780_en_sig, hd44780_regsel_sig> lcd;
typedef Console<lcd> lcd_con;

int main()
{
    cpu::init(cpu::DEFAULT);
    board::LED::port::enable();
    board::LED::output();
    lcd::init();
    lcd_con::putstr("Hello, World!");
    unsigned c = 0;
    while (true) {
        lcd::set_pos(0, 1);
        lcd_con::putdec(c++);
        delayer::delay_ms(1000);
        board::LED::toggle();
    }
}
