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
#ifndef _TIMER_TICK_HPP
#define _TIMER_TICK_HPP
#include <timer.hpp>
#include <timer_irq_dispatch.hpp>

template <typename width = uint32_t>
class Ticks : public ITimer< width, Ticks<width> >
{
protected:
    volatile static width ticks;
public:
    static void reset() { ticks = 0; }
    static void inc() { ticks++; }
    static width value() { return ticks; }

    struct Irqs : public TimerIrqsBase {
        static void overflow()
        {
            Ticks::inc();
        }
    };
};

// Explicit instantiation of static class variable - will be a COMMON symbol
// http://sourceware.org/binutils/docs/as/Comm.html#Comm
template <typename width> volatile width Ticks<width>::ticks;

// Client must bind Ticks::Irqs to a specific timer object using IRQ_DISPATCH:
//IRQ_DISPATCH(timer, Ticks<>::Irqs);

#endif // _TIMER_TICK_HPP
