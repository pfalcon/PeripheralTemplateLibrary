#include <gpio.hpp>
#include <cpu.hpp>
#include <board.hpp>
#include <delay_static.hpp>
#include <parallel_bus.hpp>


typedef StaticDelay delayer;
typedef ParBus<uint8_t, board::LED, board::LED2> leds;


int main()
{
    cpu::init(cpu::DEFAULT);
    leds::enable();
    leds::output();
    int i = 0;
    while (true) {
        leds::write(i++ % 4);
        delayer::delay(3000000U);
    }
}
