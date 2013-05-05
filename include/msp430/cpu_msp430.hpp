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
#ifndef _CPU_MSP430_HPP
#define _CPU_MSP430_HPP

#include <cpu_base.hpp>
#include <msp430.h>
#include <legacymsp430.h>

class MSP430CPU {};

// Various blocks of CPU

enum { MSP430_NONE, MSP430_TIMER, MSP430_USART, MSP430_USI, MSP430_USCI };

// All implementation of MSP430 blocks support should inherit from this class.
class MSP430Block
{
public:
    const static int block_type = MSP430_NONE;
};

/*
 * MSP430 serial communications implementation is pretty twisted thing.
 * Let's start with saying that MSP430 series has 3 different serial
 * comminication controllers: USART, USI, USCI. So, below we define
 * empty ID classes to specialize protocol implementation against.
 */

// USART is contoller in "original" MSP430 series, doesn't seem to be
// available in "value line".
struct USART {};
// USI & USCI are "value line" novelties.
// USI doesn't support UART and otherwise "lower profiler" than USCI.
struct USI {};
// USCI consists of two blocks: USCI_A & USCI_B. They appear to always
// come together, i.e. there doesn't seem to be a chip model with only
// USCI_A or USCI_B (though, with TI engineers and marketologists, you
// can only keep fingers crossed). USCI_A capable of doing UART and SPI,
// USCI_B - SPI and I2C.
struct USCI_A { const static int no = 'A'; };
struct USCI_B { const static int no = 'B'; };


template <>
class CPU<MSP430CPU> : public ICPU
{
public:
    static void init(int flags)
    {
        // Disable watchdog
        WDTCTL = WDTPW | WDTHOLD;
        switch (flags) {
        case DEFAULT:
            // Use precalibrated 1MHz frequency
            BCSCTL1 = CALBC1_1MHZ;
            DCOCTL = CALDCO_1MHZ;
            break;
        case FREQ_8MHZ:
            BCSCTL1 = CALBC1_8MHZ;
            DCOCTL = CALDCO_8MHZ;
            break;
        }
    }

    static void enable_irq()  { eint(); }
    static void disable_irq() { dint(); }
};

typedef CPU<MSP430CPU> cpu;

#endif //_CPU_MSP430_HPP
