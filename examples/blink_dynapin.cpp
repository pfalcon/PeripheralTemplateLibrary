#include <gpio.hpp>
#include <cpu.hpp>
#include <board.hpp>
#include <delay_static.hpp>
#include <delay_time.hpp>
#include <msp430/gpiodyn_msp430.hpp>

using namespace PTL;

typedef TimeDelay<board::freq, StaticDelay> delayer;

//DynaPin_Store led_spec = {board::LED::port::base, board::LED::bit::value};
DynaPin_Store led_spec(board::LED::port::no, board::LED::bit::shift);
typedef DynaPin<led_spec> dynaLED;

int main()
{
    cpu::init(cpu::DEFAULT);
    dynaLED::port::enable();
    dynaLED::output();
    while (true) {
        dynaLED::high();
        delayer::delay_ms(500);
        dynaLED::low();
        delayer::delay_ms(500);
    }
}
