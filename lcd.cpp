#include <gpio.hpp>
#include <cpu.hpp>
#include <board.hpp>
#include <delay_static.hpp>
#include <delay_time.hpp>
#include <parallel_bus.hpp>
#include <console.hpp>
#include <device/hd44780.hpp>


typedef TimeDelay<board::freq, StaticDelay> delayer;
typedef ParBus<board::D5, board::D4, board::D3, board::D2> lcd_data;
typedef Signal<board::D6> en_sig;
typedef Signal<board::D7> regsel_sig;
typedef HD44780<delayer, lcd_data, en_sig, regsel_sig> lcd;
typedef Console<lcd> lcd_con;

int main()
{
    cpu::init(cpu::DEFAULT);
    board::LED::port::enable();
    board::LED::output();
    lcd::init();
    lcd_con::putstr("Hello, World!");
    int c = 0;
    while (true) {
        lcd::set_pos(0, 1);
        lcd_con::putdec(c++);
        delayer::delay_ms(1000);
        board::LED::toggle();
    }
}
