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
#ifndef _IRQ_MSP430_HPP
#define _IRQ_MSP430_HPP

namespace PTL {

struct TimerIrqHandlers
{
    static void irq_reset();
    static void irq_capture_compare0();
    static void irq_capture_compare1();
    static void irq_capture_compare2();
};

struct CommIrqHandlers
{
    static void irq_rx();
    static void irq_tx();
};

struct ComparatorIrqHandlers
{
    static void irq_change();
};

struct AdcIrqHandlers
{
    static void irq_done();
};

struct GpioIrqHandlers
{
    static void irq_pin_change();
};

} // namespace

#endif // _IRQ_MSP430_HPP
