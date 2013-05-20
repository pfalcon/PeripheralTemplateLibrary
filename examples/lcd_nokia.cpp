#include <gpio.hpp>
#include <cpu.hpp>
#include <board.hpp>
#include <delay_static.hpp>
#include <delay_time.hpp>
#include <parallel_bus.hpp>
#include <console.hpp>
#include <device/pcd8544.hpp>

#include HW_CONFIG

typedef TimeDelay<board::freq, StaticDelay> delayer;
typedef PCD8544<delayer, pcd8544_sclk, pcd8544_sdin, pcd8544_dc, pcd8544_reset, pcd8544_sce> Lcd;
Lcd lcd;
typedef Console< WriterWrapper<Lcd, lcd> > lcd_con;

int main()
{
    cpu::init(cpu::DEFAULT);
    board::LED::port::enable();
    board::LED::output();
    lcd.begin();
    lcd.setCursor(0, 0);
    lcd_con::putstr("Hello, \nWorld!123456");
}
