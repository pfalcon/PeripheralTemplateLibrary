#include <gpio.hpp>
#include <cpu.hpp>
#include <board.hpp>
#include <delay_static.hpp>
#include <delay_time.hpp>

/*
 * Here, we just include special hardware config file, as
 * defined by PTL build system. All hardware-related definitions
 * are localized to it, and there's separate config file per
 * hardware target or subtarget. This means that source code
 * of your application does not need to be changed for particular
 * hardware setup, and you can add and change new hardware
 * setups without affecting other. Hardware config is essentially
 * just that - configuration file, so configuration of your
 * application for particular hardware target is essentially
 * data driven (syntax used in hardware config file is of course
 * C++, but that means that it's familiar and expressive).
 *
 * HW_CONFIG by default expands to "hw_config_$(TARGET).hpp",
 * i.e. build system by default assumes that if you have different
 * boards, then tehy have different architectures. You can easily
 * make it more finegrained though, just define it in your Makefile
 * to some other pattern e.g.:
 *
 * HW_CONFIG = \"hw_config_$(BOARD).hpp\"
 *
 * And build like:
 *
 * make TARGET=avr BOARD=arduino my-app
 * make TARGET=avr BOARD=custom-v2 my-app
 *
 */

#include HW_CONFIG

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
