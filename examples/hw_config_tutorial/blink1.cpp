#include <gpio.hpp>
#include <cpu.hpp>
#include <board.hpp>
#include <delay_static.hpp>
#include <delay_time.hpp>

/*
 * Simplest blink application - we use typedef to define delayer,
 * because it's too long to repeat, but use board::LED directly,
 * because it's, well, easy and obvious.
 *
 * However, if we'll want to blink another LED (board:LED2, or
 * custom one), we'll need to replace board::LED in several places.
 * So, let's proceed to blink2.
 */

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
