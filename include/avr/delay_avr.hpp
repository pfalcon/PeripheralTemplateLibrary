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
namespace PTL {

class Delay
{
public:
    typedef uint32_t width;

    static void delay(width cycles)
    {
        uint32_t d = cycles / 6;
        asm(
            "ldi    r24, %0 \n"
            "ldi    r25, %1 \n"
            "ldi    r26, %2 \n"
            "ldi    r27, %3 \n"
            "1: \n"
            "subi   r24, 1 \n" //1
            "sbci   r25, 0 \n" //1
            "sbci   r26, 0 \n" //1
            "sbci   r27, 0 \n" //1
            "brcc   1b \n"     //2
            : : "M" (d & 0xff), "M" ((d >> 8) & 0xff), "M" ((d >> 16) & 0xff), "M" ((d >> 24) & 0xff) : "r24", "r25", "r26", "r27"
        );
    }
};

} // namespace
