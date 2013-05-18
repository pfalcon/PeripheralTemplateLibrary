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
#ifndef _TIMER_BASE_HPP
#define _TIMER_BASE_HPP
#include <meta.hpp>

namespace PTL {

enum { COUNT_UP, COUNT_DOWN };

template <class timer_impl, int count_dir, typename width_, int bits = sizeof(width_) * 8>
class ITimer {
public:
    typedef width_ width;

    // Subtract 2 numbers modulo 1<<bits
    template <typename width>
    static width sub_mod(width val1, width val2, typename meta::enable_if<(bits == sizeof(width) * 8)>::type* = 0)
    {
        return val1 - val2;
    }

    // For case of bits == sizeof(width) * 8, addition and "and" should
    // optimize out. However, C standard undefines shifts for more-or-equal
    // bits than the type, and particular compilers (mspgcc) provide
    // really weird values in such case. Trying to work that around using
    // const-if still produces shift warning, so use metaprogramming if instead
    template <typename width>
    static width sub_mod(width val1, width val2, typename meta::enable_if<(bits != sizeof(width) * 8)>::type* = 0)
    {
        return (val1 - val2) & ((1U << bits) - 1);
    }

#if 0
    ALWAYS_INLINE static width sub_mod(width val1, width val2)
    {
        if (bits == sizeof(width) * 8)
            return val1 - val2;
        else
            return (val1 - val2) & ((1U << bits) - 1);
    }
#endif

    static width elapsed(width last, width prev)
    {
        if (count_dir == COUNT_UP)
            return sub_mod(last, prev);
        else
            return sub_mod(prev, last);
    }

    static bool expired(width start, width duration)
    {
        return elapsed(timer_impl::value(), start) >= duration;
    }

    static void delay_since(width since, width delay)
    {
        while (!expired(since, delay));
    }

    static void delay(width cycles)
    {
        width start = timer_impl::value();
        delay_since(start, cycles);
    }

    // Optimized version for delay width > than timer width
    // Optimized version uses as much as possible (efficient)
    // arithmetics on width, and at the same time avoid overflow issues.
    // Uses metaprogramming to enable this method only for types
    // with larger width (otherwise, may clash with delay(width) above).
    template <typename big_width>
    static void delay(big_width cycles, typename meta::enable_if<(sizeof(big_width) > sizeof(width))>::type* = 0)
    {
        width start = timer_impl::value();
        while (true) {
            width end = timer_impl::value();
            cycles -= elapsed(end, start);
            if ((typename meta::signed_t<big_width>::type)cycles < 0)
                break;
            start = end;
        }
    }
};

} // namespace

#endif // _TIMER_BASE_HPP
