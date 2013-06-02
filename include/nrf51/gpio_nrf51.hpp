/*
 * This file is part of the Peripheral Template Library project.
 *
 * Copyright (c) 2012-2013 Paul Sokolovsky <pfalcon@users.sourceforge.net>
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
#ifndef _GPIO_NRF51_HPP
#define _GPIO_NRF51_HPP

#include <gpio_base.hpp>
#include <bits.hpp>
#include <nrf51/includes_nrf51.hpp>

namespace PTL {

#undef FVAL
#define FVAL(field, val) field##_##MASK, field##_##val

template <int base_, typename width_>
class Port : public IPort<width_>
{
public:
    static const int base = base_;

    static GPIO_Type *ptr() { return (GPIO_Type*)base; }

    static void enable() {
        // Doesn't seem to be a need to enable (single in MCU) port explicitly?
    }
};

typedef Port<GPIO_P0_BASE, uint32_t> P0;

template <class port, class bit>
class Pin : public PortPin< Pin<port, bit>, port, bit >
{
public:
    static typename port::width value()
    {
        return port::ptr()->IN & bit::value;
    }
    static void high()
    {
        port::ptr()->OUTSET = bit::value;
    }
    static void low()
    {
        port::ptr()->OUTCLR = bit::value;
    }
    static void toggle()
    {
        port::ptr()->OUT ^= bit::value;
    }

    static void output()
    {
        // nRF51 refman 13.1 p.56: "Pin direction can be configured both in
        // the DIR register as well as through the individual PIN_CNF[n]
        // registers. A change in one register will automatically be
        // reflected in the other register.
        port::ptr()->DIRSET = bit::value;
        // nRF51 refman 13.1 p.55: "The input buffer of a GPIO pin can be
        // disconnected from the pin to enable power savings when the pin is
        // not used as an input. Inputs must be connected in order to get a
        // valid input value in the IN register and for the sense mechanism
        // to get access to the pin.
        SET_BITFIELD(port::ptr()->PIN_CNF[bit::shift], FVAL(GPIO_PIN_CNF_INPUT, DISCONNECT));
    }
    static void input()
    {
        // See output() comments
        SET_BITFIELD(port::ptr()->PIN_CNF[bit::shift], FVAL(GPIO_PIN_CNF_INPUT, CONNECT));
        port::ptr()->DIRCLR = bit::value;
    }

    static void pulloff()
    {
        volatile uint32_t *reg = &port::ptr()->PIN_CNF[bit::shift];
        SET_BITFIELD(*reg, FVAL(GPIO_PIN_CNF_PULL, DISABLED));
    }
    static void pullup()
    {
        volatile uint32_t *reg = &port::ptr()->PIN_CNF[bit::shift];
        SET_BITFIELD(*reg, FVAL(GPIO_PIN_CNF_PULL, PULLUP));
    }
    static void pulldown()
    {
        volatile uint32_t *reg = &port::ptr()->PIN_CNF[bit::shift];
        SET_BITFIELD(*reg, FVAL(GPIO_PIN_CNF_PULL, PULLDOWN));
    }
};

} // namespace

#endif //_GPIO_NRF51_HPP
