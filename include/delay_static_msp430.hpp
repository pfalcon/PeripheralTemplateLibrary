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
template <long cycles, bool toobig = (cycles > 32767)>
class MSP430Delay
{
public:
    static void delay()
    {
        __delay_cycles(cycles);
    }
};

template <long cycles>
class MSP430Delay<cycles, true>
{
public:
    static void delay()
    {
        for (int i = cycles / 32765; i; i--)
            __delay_cycles(32765);
        __delay_cycles(cycles % 32765);
    }
};

template <long cycles>
inline void delay()
{
    MSP430Delay<cycles>::delay();
}
