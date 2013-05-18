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

#include <msp430.h>

namespace PTL {

// 1MHz / 3 = 333KHz
#define FLASH_CLOCK_DIV 3

#define FLASH_SEGMENT_D 0x1000

class Flash
{
public:
        static void init()
        {
            // MCLK should be 1MHz
            FCTL2 = FWKEY | FSSEL_1 | (FLASH_CLOCK_DIV - 1);
        }

        static void erase(void *block)
        {
            // Watchdog should be disabled
            // Reset LOCK and other status bits
            FCTL3 = FWKEY;
            FCTL1 = FWKEY | ERASE;
            *(uint8_t*)block = 0;
            FCTL1 = FWKEY;
            FCTL3 = FWKEY | LOCK;
        }

        static void write8(uint8_t *addr, uint8_t val)
        {
            // Reset LOCK and other status bits
            FCTL3 = FWKEY;
            FCTL1 = FWKEY | WRT;
            *addr = val;
            FCTL1 = FWKEY;
            FCTL3 = FWKEY | LOCK;
        }

        static void write16(uint16_t *addr, uint16_t val)
        {
            // Reset LOCK and other status bits
            FCTL3 = FWKEY;
            FCTL1 = FWKEY | WRT;
            *addr = val;
            FCTL1 = FWKEY;
            FCTL3 = FWKEY | LOCK;
        }
};

} // namespace
