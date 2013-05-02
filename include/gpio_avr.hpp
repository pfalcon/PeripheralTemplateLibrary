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
#ifndef _GPIO_AVR_HPP
#define _GPIO_AVR_HPP

#include <gpio_base.hpp>
// Make register defines be just integer addresses
#define _SFR_ASM_COMPAT 1
#include <avr/io.h>


template <int in_reg_, int out_reg_, int dir_reg_, typename width_>
class Port : public IPort<width_>
{
public:
    static const int in_reg = in_reg_;
    static const int out_reg = out_reg_;
    static const int dir_reg = dir_reg_;
};

#ifdef PINA
typedef Port<PINA, PORTA, DDRA, uint8_t> PA;
#endif
#ifdef PINB
typedef Port<PINB, PORTB, DDRB, uint8_t> PB;
#endif
#ifdef PINC
typedef Port<PINC, PORTC, DDRC, uint8_t> PC;
#endif
#ifdef PIND
typedef Port<PIND, PORTD, DDRD, uint8_t> PD;
#endif

template <class port, class bit>
class Pin : public PortPin< Pin<port, bit>, port, bit >
{
public:
    static uint8_t value()
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
    static void toggle()
    {
        *(volatile uint8_t*)port::out_reg ^= bit::value;
    }
    static void output()
    {
        *(volatile uint8_t*)port::dir_reg |= bit::value;
    }
    static void input()
    {
        *(volatile uint8_t*)port::dir_reg &= ~bit::value;
    }
};

#endif //_GPIO_AVR_HPP
