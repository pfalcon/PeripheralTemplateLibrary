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
#ifndef _CPU_AVR_HPP
#define _CPU_AVR_HPP
#include <types.hpp>
#include <cpu_base.hpp>
#include <avr/wdt.h>

class AVRCPU {};

template <>
class CPU<AVRCPU> : public ICPU
{
public:
    static void init(int flags)
    {
        // Disable hwuart enabled by Arduino bootloader
        _R8(UCSR0B) = 0;
#if 0
        switch (flags) {
        case DEFAULT:
            wdt_disable();
            break;
        }
#endif
    }
};

typedef CPU<AVRCPU> cpu;

#endif //_CPU_AVR_HPP
