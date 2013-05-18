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
#include <board_base.hpp>
#include <gpio.hpp>
#include <clock.hpp>

namespace PTL {

class EFM32GGSTK3700 {};

template <>
class Board<EFM32GGSTK3700>
{
public:
    typedef Pin<PE, Bit2> LED;
    typedef Pin<PE, Bit3> LED2;
    static const long freq = 48 MHZ;
};

typedef Board<EFM32GGSTK3700> board;

} // namespace
