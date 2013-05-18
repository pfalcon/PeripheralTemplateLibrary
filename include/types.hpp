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
#ifndef _TYPES_HPP
#define _TYPES_HPP

#include <stdint.h>

namespace PTL {

typedef uint8_t bool8;

class None {};

typedef void (*IrqHandler)();

// Helpers to access iomem registers
#define _REG8(addr) (*(volatile uint8_t*)(addr))
#define _REG16(addr) (*(volatile uint16_t*)(addr))
#define _REG32(addr) (*(volatile uint32_t*)(addr))
// AVR compat. TODO: get rid of these?
#ifndef _R8
#define _R8(addr) _REG8(addr)
#define _R16(addr) _REG16(addr)
#define _R32(addr) _REG32(addr)
#endif

} // namespace

#endif //_TYPES_HPP
