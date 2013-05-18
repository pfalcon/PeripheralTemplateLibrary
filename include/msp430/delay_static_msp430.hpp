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

#include <stdint.h>
#include <inline.hpp>

namespace PTL {

static ALWAYS_INLINE void __delay_cycles2(long delay)
{
//  if (__builtin_constant_p(delay)) {
    if (delay == 1) {
        asm("nop");
    } else if (delay == 2) {
        asm("nop");
        asm("nop");
    } else if (delay == 3) {
        asm("nop");
        asm("nop");
        asm("nop");
    } else if (delay <= 196611) {
        int quot, rem, quot2, rem2;
        quot = (delay - 1) / 3;
        rem = (delay - 1) % 3;
        if (!(quot == 1 || quot == 2 || quot == 4 || quot == 8)) {
            // Cannot use constant generator (1 cycle to load constant),
            // have to use immediate constant (2 cycles)
            quot = (delay - 2) / 3;
            rem = (delay - 2) % 3;
            // Well, there's exception
            if (quot == 1 || quot == 2 || quot == 4 || quot == 8)
                rem++;
        }

        if (rem == 1) {
            asm("nop");
        } else if (rem == 2) {
            asm("nop");
            asm("nop");
        } else if (rem == 3) {
            asm("nop");
            asm("nop");
            asm("nop");
        }

        asm __volatile__ (
            "mov    %0, r15 \n"
            "1: \n"
            "dec    r15 \n" // 1 cycle
            "jnz    1b \n" // 2 cycles, msp430 has weird C flag value for substracts
            : : "ir" (quot) : "r15"
        );
    } else {
        long quot;
        int rem;
        quot = (delay - 4) / 4 - 1; // cycles stops on 0 -> -1 transition, i.e. 1 extra iteration
        rem = (delay - 4) % 4;

        asm(
            "mov    %A0, r14 \n"
            "mov    %B0, r15 \n"
            "1: \n"
            "sub    #1, r14 \n" // 1 cycle
            "subc   #0, r15 \n" // 1 cycle
            "jc    1b \n" // 2 cycles, msp430 has weird C flag value for substracts
            : : "ir" (quot) : "r14", "r15"
        );

        // It might be possible to optimize these, but it's boring
        uint16_t low = (uint16_t)quot;
        uint16_t hiw = quot >> 16;
        if (low == 0 || low == 1 || low == 2 || low == 4 || low == 8)
            rem++;
        if (hiw == 0 || hiw == 1 || hiw == 2 || hiw == 4 || hiw == 8)
            rem++;

        if (rem >= 1) {
            asm("nop");
        }
        if (rem >= 2) {
            asm("nop");
        }
        if (rem >= 3) {
            asm("nop");
        }
        if (rem >= 4) {
            asm("nop");
        }
        if (rem >= 5) {
            asm("nop");
        }
    }

//  }
}


class StaticDelay
{
public:
    ALWAYS_INLINE static void delay(long cycles)
    {
        __delay_cycles2(cycles);
    }
};

} // namespace
