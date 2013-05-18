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
#ifndef _WATCHDOG_MSP430_HPP
#define _WATCHDOG_MSP430_HPP

namespace PTL {

class Watchdog
{
public:
    const static uint16_t SMCLK = 0;
    const static uint16_t ACLK = WDTSSEL;

    const static uint16_t INTERVAL_32768 = 0;
    const static uint16_t INTERVAL_8192  = 1;
    const static uint16_t INTERVAL_512   = 2;
    const static uint16_t INTERVAL_64    = 3;

    template <class clock>
    static void enable_watchdog(uint16_t interval)
    {
        // slau144i 10.2.3 p.352 "The WDT+ should be halted before changing
        // the clock source to avoid a possible incorrect interval."
        disable();
        WDTCTL = WDTPW | WDTCNTCL | clock::as_watchdog_clock() | interval;
    }

    template <class clock>
    static void set_interval(uint16_t interval)
    {
        // Warning:
        // slau144i 10.2.3 p.352 "The WDT+ should be halted before changing
        // the clock source to avoid a possible incorrect interval."
        WDTCTL = WDTPW | WDTTMSEL | WDTCNTCL | clock::as_watchdog_clock() | interval;
    }

    template <class clock>
    static void enable_interval(uint16_t interval)
    {
        // slau144i 10.2.3 p.352 "The WDT+ should be halted before changing
        // the clock source to avoid a possible incorrect interval."
        disable();
        set_interval<clock>(interval);
    }

    static void disable() { WDTCTL = WDTPW | WDTHOLD; }
    static void reset() { WDTCTL = WDTPW | ((WDTCTL & 0xff) | WDTCNTCL); }
    static void enable_irq()  { IE1 |= WDTIE; }
    static void disable_irq() { IE1 &= ~WDTIE; }
};

} // namespace

#endif //_WATCHDOG_MSP430_HPP
