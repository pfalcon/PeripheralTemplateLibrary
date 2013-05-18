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
#ifndef _BOARD_LAUNCHPAD_STELLARIS_HPP
#define _BOARD_LAUNCHPAD_STELLARIS_HPP

#include <board_base.hpp>
#include <gpio.hpp>
#include <clock.hpp>

namespace PTL {

class StellarisLaunchpad {};

template <>
class Board<StellarisLaunchpad>
{
public:
    // Red color of RGB LED
    typedef Pin<PF, Bit1> LED;
    // Blue color of RGB LED
    typedef Pin<PF, Bit2> LED2;
    // Green color of RGB LED
    typedef Pin<PF, Bit3> LED3;

    // Precision Oscillator (PIOSC): On-chip resource providing
    // a 16 MHz ±1% frequency at room temperature
    static const long freq = 16 MHZ;
};

typedef Board<StellarisLaunchpad> board;

} // namespace

#endif // _BOARD_LAUNCHPAD_STELLARIS_HPP
