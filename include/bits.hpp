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
#ifndef _BITS_HPP
#define _BITS_HPP

namespace PTL {

template <int bit>
class Bit
{
public:
    static const int value = 1 << bit;
    static const int shift = bit;
};

typedef Bit<0> Bit0;
typedef Bit<1> Bit1;
typedef Bit<2> Bit2;
typedef Bit<3> Bit3;
typedef Bit<4> Bit4;
typedef Bit<5> Bit5;
typedef Bit<6> Bit6;
typedef Bit<7> Bit7;
typedef Bit<8> Bit8;
typedef Bit<9> Bit9;
typedef Bit<10> Bit10;
typedef Bit<11> Bit11;
typedef Bit<12> Bit12;
typedef Bit<13> Bit13;
typedef Bit<14> Bit14;
typedef Bit<15> Bit15;

// Bitfield manipulation helpers, these assume value and mask already shifted
// to correspond to physical bit positions.
#define GET_BITFIELD(lval, mask)  ((lval) & (mask))
#define SET_BITFIELD(lval, mask, field_val)  (lval = (((lval) & (mask)) | (field_val)))

} // namespace

#endif //_BITS_HPP
