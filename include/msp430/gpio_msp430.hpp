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
#ifndef _GPIO_MSP430_HPP
#define _GPIO_MSP430_HPP

#include <types.hpp>
#include <gpio_base.hpp>
#include <msp430.h>

namespace PTL {

template <int in_reg_, int out_reg_, int dir_reg_, int resistor_reg_, typename width_>
class Port : public IPort<width_>
{
public:
    static const int in_reg = in_reg_;
    static const int out_reg = out_reg_;
    static const int dir_reg = dir_reg_;
    static const int resistor_reg = resistor_reg_;
};

template <int in_reg_, int out_reg_, int dir_reg_, int resistor_reg_, int ifg_reg_, int ies_reg_, int ie_reg_, typename width_>
class IntPort : public Port<in_reg_, out_reg_, dir_reg_, resistor_reg_, width_>
{
public:
    static const int ifg_reg = ifg_reg_;
    static const int ies_reg = ies_reg_;
    static const int ie_reg = ie_reg_;
};

typedef IntPort<P1IN_, P1OUT_, P1DIR_, P1REN_, P1IFG_, P1IES_, P1IE_, uint8_t> P1;
typedef IntPort<P2IN_, P2OUT_, P2DIR_, P2REN_, P2IFG_, P2IES_, P2IE_, uint8_t> P2;
typedef Port<P3IN_, P3OUT_, P3DIR_, P3REN_, uint8_t> P3;

template <class port, class bit>
class Pin : public PortPin< Pin<port, bit>, port, bit >
{
public:
    static typename port::width value()
    {
        return _REG8(port::in_reg) & bit::value;
    }
    static void high()
    {
        _REG8(port::out_reg) |= bit::value;
    }
    static void low()
    {
        _REG8(port::out_reg) &= ~bit::value;
    }
    static void toggle()
    {
        _REG8(port::out_reg) ^= bit::value;
    }
    static void output()
    {
        _REG8(port::dir_reg) |= bit::value;
    }
    static void input()
    {
        _REG8(port::dir_reg) &= ~bit::value;
    }
    static void pulloff()
    {
        _REG8(port::resistor_reg) &= ~bit::value;
    }
    static void pullup()
    {
        _REG8(port::resistor_reg) |= bit::value;
        _REG8(port::out_reg) |= bit::value;
    }
    static void pulldown()
    {
        _REG8(port::resistor_reg) |= bit::value;
        _REG8(port::out_reg) &= ~bit::value;
    }
};

template <class port, class bit>
class IntPin : public Pin<port, bit>
{
public:
    static void rising_edge_irq()
    {
        _REG8(port::ies_reg) |= bit::value;
    }
    static void falling_edge_irq()
    {
        _REG8(port::ies_reg) &= ~bit::value;
    }
    static void enable_irq()
    {
        _REG8(port::ie_reg) |= bit::value;
    }
    static void disable_irq()
    {
        _REG8(port::ie_reg) &= ~bit::value;
    }
    static void clear_ifg()
    {
        _REG8(port::ifg_reg) &= ~bit::value;
    }
};

} // namespace

#endif //_GPIO_MSP430_HPP
