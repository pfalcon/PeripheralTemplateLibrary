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

#include <msp430.h>
#include <legacymsp430.h>
#include <cpu.hpp>
#include <clock.hpp>
#include <watchdog_msp430.hpp>

class Sleep
{
public:
    static void sleep(uint16_t interval)
    {
        Watchdog::enable_interval<ACLK>(interval);
        Watchdog::enable_irq();
        cpu::enable_irq();
        LPM3;
    }

    static interrupt (WDT_VECTOR) watchdog_isr()
    {
        // Disable watchdog again
        Watchdog::disable();
        LPM3_EXIT;
    }
};
