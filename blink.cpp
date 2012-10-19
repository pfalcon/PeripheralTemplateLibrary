#include <gpio.hpp>
#include <cpu.hpp>
#include <board.hpp>
#include <delay_static.hpp>
#include <delay_time.hpp>


typedef TimeDelay<board::freq, StaticDelay> delayer;

int main()
{
    cpu::init(cpu::DEFAULT);
    board::LED::port::enable();
    board::LED::output();
    while (true) {
        board::LED::high();
        delayer::delay_ms(500);
        board::LED::low();
        delayer::delay_ms(500);
    }
}
