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
#ifndef _BOARD_LAUNCHPAD_MSP430_HPP
#define _BOARD_LAUNCHPAD_MSP430_HPP

#include <board_base.hpp>
#include <gpio.hpp>
#include <clock.hpp>

namespace PTL {

class MSP430Launchpad {};

template <>
class Board<MSP430Launchpad>
{
public:
    // Left, red LED
    typedef Pin<P1, Bit0> LED;
    // Right, green LED, conflicts with SPI, I2C
    typedef Pin<P1, Bit6> LED2;
    // This is HWUART pin mapping. On 1.5, jumpers should be
    // put in perpindicular position wrt other jumpers. Not
    // compatible with Launchpad 1.4, where tx & rx should be
    // swapped.
    typedef Pin<P1, Bit2> pin_uart_tx;
    typedef Pin<P1, Bit1> pin_uart_rx;
    static const long freq = 1 MHZ;
};

typedef Board<MSP430Launchpad> board;

} // namespace

#endif // _BOARD_LAUNCHPAD_MSP430_HPP
