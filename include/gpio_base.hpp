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
#ifndef _GPIO_BASE_HPP
#define _GPIO_BASE_HPP

#include <stdio.h>
#include <stdint.h>
#include <bits.hpp>
#include <types.hpp>
#include <inline.hpp>

namespace PTL {

// Pin is abstraction of basic I/O signal
template <class pin_impl>
class IPin
{
public:
    static void enable();
    static void output();
    static void input();
    // TODO: need better type
    static int  value();
    static void high();
    static void low();
    static void toggle();
    static void set(bool8 val)
    {
        if (val)
            pin_impl::high();
        else
            pin_impl::low();
    }
    static void pulloff();
    static void pullup();
    static void pulldown();
};

// Port is a collection of related pins
template <typename width_>
class IPort
{
public:
    typedef width_ width;

    // Enable port for access (power on, set up clocks, etc.)
    static void enable() {}
    // Disable port (power off)
    static void disable() {}

    static width value();
    static void set(width val);
    static void set_masked(width val, width mask) { set(value() & mask); }
};

// Pin which belongs to a port
template <class pin_impl, class port_, class bit_>
class PortPin: public IPin<pin_impl>
{
public:
    typedef port_ port;
    typedef bit_ bit;

    static void enable() { port::enable(); }
};

// Non-existent pin, can be used when a pin in some design is optional.
// All access will be optimized out by compiler.
class NullPin : public IPin<NullPin>
{
public:
    typedef class NullPort {} port;
    ALWAYS_INLINE static void output() {}
    ALWAYS_INLINE static void high() {}
    ALWAYS_INLINE static void low()  {}
    ALWAYS_INLINE static void toggle() {}
    ALWAYS_INLINE static void set(bool8 val) {}
};

} // namespace

#endif //_GPIO_BASE_HPP
