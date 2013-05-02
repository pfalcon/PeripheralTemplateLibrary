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
#ifndef _GPIO_EFM32_HPP
#define _GPIO_EFM32_HPP

#include <gpio_base.hpp>
#include <efm32gg990f1024.h>


template <int port_no_, typename width_>
class Port : IPort
{
public:
    static const int port_no = port_no_;
    typedef width_ width;

    static void enable() {
        CMU->HFPERCLKDIV |= CMU_HFPERCLKDIV_HFPERCLKEN;
        CMU->HFPERCLKEN0 |= CMU_HFPERCLKEN0_GPIO;
//        CMU_ClockEnable(cmuClock_HFPER, true);
//        CMU_ClockEnable(cmuClock_GPIO, true);
    }
};

typedef Port<0, uint16_t> PA;
typedef Port<1, uint16_t> PB;
typedef Port<2, uint16_t> PC;
typedef Port<3, uint16_t> PD;
typedef Port<4, uint16_t> PE;
typedef Port<5, uint16_t> PF;

template <class port, class bit>
class Pin : public PortPin< Pin<port, bit>, port, bit >
{
    static void set_mode(int mode)
    {
        volatile uint32_t *reg;
        if (bit::shift < 8)
            reg  = &GPIO->P[port::port_no].MODEL;
        else
            reg  = &GPIO->P[port::port_no].MODEH;

        uint32_t mask = 0xf << ((bit::shift % 8) * 4);
        uint32_t val  = mode << ((bit::shift % 8) * 4);
        *reg = (*reg & ~mask) | val;
    }

public:
    static typename port::width value()
    {
        return GPIO->P[port::port_no].DIN & bit::value;
    }
    static void high()
    {
        GPIO->P[port::port_no].DOUTSET = bit::value;
    }
    static void low()
    {
        GPIO->P[port::port_no].DOUTCLR = bit::value;
    }

    static void output()
    {
        set_mode(_GPIO_P_MODEL_MODE0_PUSHPULL);
    }
    static void input()
    {
        set_mode(_GPIO_P_MODEL_MODE0_INPUT);
    }
};

#endif //_GPIO_EFM32_HPP
