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

#include <gpio_base.hpp>
#include <msp430.h>


template <int in_reg_, int out_reg_, int dir_reg_, int resistor_reg_, typename width_>
class Port : public IPort
{
public:
    static const int in_reg = in_reg_;
    static const int out_reg = out_reg_;
    static const int dir_reg = dir_reg_;
    static const int resistor_reg = resistor_reg_;
    typedef width_ width;
};

typedef Port<P1IN_, P1OUT_, P1DIR_, P1REN_, uint8_t> P1;
typedef Port<P2IN_, P2OUT_, P2DIR_, P2REN_, uint8_t> P2;

template <class port_, class bit>
class Pin : IPin
{
public:
    typedef port_ port;

    static typename port::width value()
    {
        return *(volatile uint8_t*)port::in_reg & bit::value;
    }
    static void high()
    {
        *(volatile uint8_t*)port::out_reg |= bit::value;
    }
    static void low()
    {
        *(volatile uint8_t*)port::out_reg &= ~bit::value;
    }
    static void output()
    {
        *(volatile uint8_t*)port::dir_reg |= bit::value;
    }
    static void input()
    {
        *(volatile uint8_t*)port::dir_reg &= ~bit::value;
    }
    static void pulloff()
    {
        *(volatile uint8_t*)port::resistor_reg &= ~bit::value;
    }
    static void pullup()
    {
        *(volatile uint8_t*)port::resistor_reg |= bit::value;
        *(volatile uint8_t*)port::out_reg |= bit::value;
    }
    static void pulldown()
    {
        *(volatile uint8_t*)port::resistor_reg |= bit::value;
        *(volatile uint8_t*)port::out_reg &= ~bit::value;
    }
};

#endif //_GPIO_MSP430_HPP
