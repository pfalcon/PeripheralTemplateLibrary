#include <gpio.hpp>
#include <cpu.hpp>
#include <board.hpp>
#include <clock.hpp>
#include <sleep.hpp>
#include <sleep_impl.hpp>

using namespace PTL;

int main()
{
    cpu::init(cpu::DEFAULT);
    ACLK::source<VLOCLK, DIV_4>();
    board::LED::port::enable();
    board::LED::output();
    while (true) {
        board::LED::toggle();
        Sleep::sleep(Watchdog::INTERVAL_512);
    }
}
