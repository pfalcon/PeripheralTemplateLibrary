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
#ifndef _TIMER_AVR_HPP
#define _TIMER_AVR_HPP

#include <timer_base.hpp>
#include <cpu_avr.hpp>

class Timer1 : public ITimer<Timer1, uint16_t>
{
public:
    static width value() { return _R16(TCNT1); }
    static void free_run()
    {
        _R8(TCCR1A) = 0;
        _R8(TCCR1B) = _BV(CS10);
    }

};

typedef Timer1 timer;

#endif // _TIMER_AVR_HPP
