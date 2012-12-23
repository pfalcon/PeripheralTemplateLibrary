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
//#include <libopencm3/stm32/f1/rcc.h>
//#include <libopencm3/EFM32/f1/gpio.h>
#include <em_cmu.h>
#include <em_gpio.h>


template <int port_no_, typename width_>
class Port : IPort
{
public:
    static const int port_no = port_no_;
    typedef width_ width;

    static void enable() {
        CMU_ClockEnable(cmuClock_HFPER, true);
        CMU_ClockEnable(cmuClock_GPIO, true);
    }
};

typedef Port<gpioPortA, uint16_t> PA;
typedef Port<gpioPortB, uint16_t> PB;
typedef Port<gpioPortC, uint16_t> PC;
typedef Port<gpioPortD, uint16_t> PD;
typedef Port<gpioPortE, uint16_t> PE;
typedef Port<gpioPortF, uint16_t> PF;

template <class port_, class bit>
class Pin : IPin< Pin<port_, bit> >
{
    static void set_mode(int mode)
    {
        GPIO_PinModeSet((GPIO_Port_TypeDef)port::port_no, bit::shift, (GPIO_Mode_TypeDef)mode, 0);
    }

public:
    typedef port_ port;

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
        set_mode(gpioModePushPull);
    }
    static void input()
    {
        set_mode(gpioModeInput);
    }
};

#endif //_GPIO_EFM32_HPP
