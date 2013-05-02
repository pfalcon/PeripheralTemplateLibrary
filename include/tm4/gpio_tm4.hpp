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
#ifndef _GPIO_LM4_HPP
#define _GPIO_LM4_HPP

#include <gpio_base.hpp>
#include <bits.hpp>
#include <tm4/includes_tm4.hpp>


template <int base_, typename width_>
class Port : public IPort<width_>
{
public:
    static const int base = base_;

    static GPIO_Type *ptr() { return (GPIO_Type*)base; }

    static void enable() {
        switch (base) {
        case GPIOA_BASE:
            SYSCTL->RCGCGPIO |= Bit0::value;
            break;
        case GPIOB_BASE:
            SYSCTL->RCGCGPIO |= Bit1::value;
            break;
        case GPIOC_BASE:
            SYSCTL->RCGCGPIO |= Bit2::value;
            break;
        case GPIOD_BASE:
            SYSCTL->RCGCGPIO |= Bit3::value;
            break;
        case GPIOE_BASE:
            SYSCTL->RCGCGPIO |= Bit4::value;
            break;
        case GPIOF_BASE:
            SYSCTL->RCGCGPIO |= Bit5::value;
            break;
        }
    }
};

typedef Port<GPIOA_BASE, uint8_t> PA;
typedef Port<GPIOB_BASE, uint8_t> PB;
typedef Port<GPIOC_BASE, uint8_t> PC;
typedef Port<GPIOD_BASE, uint8_t> PD;
typedef Port<GPIOE_BASE, uint8_t> PE;
typedef Port<GPIOF_BASE, uint8_t> PF;

template <class port, class bit>
class Pin : public PortPin< Pin<port, bit>, port, bit >
{
public:
    static typename port::width value()
    {
        return port::ptr()->DATA & bit::value;
    }
    static void high()
    {
        (&port::ptr()->DATA_START)[bit::value] = 0xff;
    }
    static void low()
    {
        (&port::ptr()->DATA_START)[bit::value] = 0x00;
    }
    static void toggle()
    {
        port::ptr()->DATA ^= bit::value;
    }

    static void output()
    {
        port::ptr()->DIR |= bit::value;
        enable();
    }
    static void input()
    {
        port::ptr()->DIR &= ~bit::value;
        enable();
    }
    static void enable()
    {
        port::ptr()->DEN |= bit::value;
    }
    static void disable()
    {
        port::ptr()->DEN &= ~bit::value;
    }

    static void altfunc(uint32_t func)
    {
        port::ptr()->AFSEL |= bit::value;
        uint32_t mask = 0xf << (bit::shift * 4);
        port::ptr()->PCTL = (port::ptr()->PCTL & ~mask) | (func << (bit::shift * 4));
    }
};

#endif //_GPIO_LM4_HPP
