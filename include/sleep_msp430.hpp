/*
 * This file is part of the Peripheral Template Library project.
 *
 * Copyright (c) 2012 Paul Sokolovsky <pfalcon@users.sourceforge.net>
 *
 * This library is free software: you can redistribute it and/or modify
 * it under the terms of the GNU Lesser General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public License
 * along with this library.  If not, see <http://www.gnu.org/licenses/>.
 */
#ifndef _SLEEP_MSP430_HPP
#define _SLEEP_MSP430_HPP

#include <msp430.h>
#include <legacymsp430.h>
#include <cpu.hpp>
#include <clock.hpp>
#include <watchdog_msp430.hpp>
#include <adc.hpp>

#define strong_cast(type, lval) (*(type*)&lval)

class Sleep
{
    static uint32_t _interval;

    static void set_iteration()
    {
        if (_interval >= 32768) {
            _interval -= 32768;
            Watchdog::enable_interval<ACLK>(Watchdog::INTERVAL_32768);
        } else if (_interval >= 8192) {
            strong_cast(uint16_t, _interval) -= 8192;
            Watchdog::enable_interval<ACLK>(Watchdog::INTERVAL_8192);
        } else if (_interval >= 512) {
            strong_cast(uint16_t, _interval) -= 512;
            Watchdog::enable_interval<ACLK>(Watchdog::INTERVAL_512);
        } else {
            if (_interval > 64)
                strong_cast(uint16_t, _interval) -= 64;
            else
                _interval = 0;
            Watchdog::enable_interval<ACLK>(Watchdog::INTERVAL_64);
        }
    }

public:
    static void sleep(uint32_t interval)
    {
        // Minimum interval is 64. If we were asked to sleep, then they want
        // us to sleep (i.e. save power), so let's sleep at least that much.
        _interval = interval;
        set_iteration();
        Watchdog::enable_irq();
        cpu::enable_irq();
        LPM3;
    }

    static interrupt (WDT_VECTOR) watchdog_isr()
    {
        if (_interval == 0) {
            // Disable watchdog again
            Watchdog::disable();
            LPM3_EXIT;
        } else {
            // Wait again within LPM3
            set_iteration();
        }
    }

    // Powerdown system, making it consume as little power
    // as possible. Usecase: battery-power design w/o power
    // button. It works for limited time and then auto powers
    // off. To start again, push reset button which is often
    // available, unlike the power switch.
    static void powerdown()
    {
        cpu::disable_irq();
        ADC::disable();
        LPM4;
    }
};

#endif //_SLEEP_MSP430_HPP
