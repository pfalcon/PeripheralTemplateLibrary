#include <gpio.hpp>
#include <cpu.hpp>
#include <board.hpp>
#include <delay_static.hpp>
#include <delay_time.hpp>

/*
 * Here, we (type)define led blink once at the beginning of the
 * program, so it's easy to redefine it to board::LED2,
 * Pin<PA, Bit3> or whatever.
 *
 * However, what if our application is not such simple, consists
 * of many modules, or targetted to completely different boards?
 * Proceed to blink3.
 */

typedef TimeDelay<board::freq, StaticDelay> delayer;
typedef board::LED led;

int main()
{
    cpu::init(cpu::DEFAULT);
    led::port::enable();
    led::output();
    while (true) {
        led::high();
        delayer::delay_ms(500);
        led::low();
        delayer::delay_ms(500);
    }
}
