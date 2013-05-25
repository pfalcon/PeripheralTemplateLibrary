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
#include <types.hpp>

namespace PTL {

inline void __delay_cycles2(uint32_t cycles)
{
    if (cycles == 0) {
        ;
    } else if (cycles == 1) {
        asm("add r0, #0"); // don't set flags!
        // Data operations | 32 | 1
    } else if (cycles == 2) {
        // Single branch won't work here, because if next
        // instr is unaligned 32bit one, branch will take 3 cycles
        asm("add r0, #0"); // don't set flags!
        asm("add r0, #0"); // don't set flags!
    } else if (cycles == 3) {
        asm("b 1f \n"); // Branches 16 1+P
        asm("1: \n");
        asm("add r0, #0");
        // TRM p.18-5 Taken branches with an immediate are normally 1 cycle of pipeline reload (2 cycles total).
    } else {
        uint32_t loop_count = ((cycles - 1) + 2) / 3;
        asm __volatile__ (
            // Following 2 commands are rendered by gcc, and just typical
            // Compiler may preload the value to another registers and then
            // just do mov rA, rB - that typically happens when using same
            // delay value in close statements or when doing loop invariant
            // lifting.
            //"movw %[value], #low \n" //1
            //"movt %[value], #high \n" //1
            // or
            //"mov %[value], %another_reg \n" //1

            "1: \n"
            "subs %[value], #1 \n" //1
            "bne 1b \n" // 2
            : [value] "+r" (loop_count) :
        );
        // 2 + 3*(N-1) + (1-2) == 3*N (+1)
    }
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
