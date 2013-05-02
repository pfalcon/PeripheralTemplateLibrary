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
#ifndef _GPIO_STM32_HPP
#define _GPIO_STM32_HPP

#include <gpio_base.hpp>
#include <includes_stm32.hpp>


template <int base_, typename width_>
class Port : public IPort<width_>
{
public:
    static const int base = base_;

    static GPIO_TypeDef *ptr() { return (GPIO_TypeDef*)base; }

    static void enable() {
        switch (base) {
        case GPIOA_BASE:
            RCC->APB2ENR |= RCC_APB2ENR_IOPAEN;
            break;
        case GPIOB_BASE:
            RCC->APB2ENR |= RCC_APB2ENR_IOPBEN;
            break;
        case GPIOC_BASE:
            RCC->APB2ENR |= RCC_APB2ENR_IOPCEN;
            break;
        case GPIOD_BASE:
            RCC->APB2ENR |= RCC_APB2ENR_IOPDEN;
            break;
        }
    }
};

typedef Port<GPIOA_BASE, uint16_t> PA;
typedef Port<GPIOB_BASE, uint16_t> PB;
typedef Port<GPIOC_BASE, uint16_t> PC;
typedef Port<GPIOD_BASE, uint16_t> PD;

template <class port, class bit>
class Pin : public PortPin< Pin<port, bit>, port, bit >
{
    static void set_mode(int mode)
    {
        volatile uint32_t *reg;
        if (bit::shift < 8)
            reg  = &port::ptr()->CRL;
        else
            reg  = &port::ptr()->CRH;
        uint32_t mask = 0xf << ((bit::shift % 8) * 4);
        uint32_t val  = mode << ((bit::shift % 8) * 4);
        *reg = (*reg & ~mask) | val;
    }

public:
    typedef port_ port;

    static typename port::width value()
    {
        return port::ptr()->IDR & bit::value;
    }
    static void high()
    {
        port::ptr()->BSRR = bit::value;
    }
    static void low()
    {
        port::ptr()->BRR = bit::value;
    }
    static void toggle()
    {
        port::ptr()->ODR ^= bit::value;
    }

    static void output()
    {
        set_mode(0x02);
    }
    static void input()
    {
        set_mode(0x04);
    }
};

#endif //_GPIO_STM32_HPP
