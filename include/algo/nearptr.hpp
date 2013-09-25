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
#ifndef _NEAR_PTR_HPP
#define _NEAR_PTR_HPP
// As C++ doesn't support overloading templates by parameters, we should name
// all templates differently. Also, "const char *" template parameter cannot
// be cast to int. So, we have 3 templates with the same implementation,
// difgering only in type of base template parameter.

#define IMPL(name) \
public: \
    storage_t off; \
    name() { off = 0; } \
    name(T *p) { off = ((int)p - (int)base) >> align; } \
    T& operator*() const { return *(T*)((int)base + (off << align)); } \
    operator T*() const { return (T*)((int)base + (off << align)); }

// NearPtr against absolute base. This is what would be used on
// MCU platform.
// Params:
// base - base of the memoty region within which pointer will point
// storage_t - size of pointer value (uint8_t, uint16_t, etc.); can be
//             signed type too if needed
// T - type to point to
// align - alignment of pointer, as power of 2
// For example, 16-bit NearPtr with alignment of 16 can address 1MB of memory
template <int base, typename storage_t, typename T, int align = 0> class AbsNearPtr
{
    IMPL(AbsNearPtr)
};

// NearPtr against statically allocated array (note: must have external
// linkage, i.e. defined globally w/o static keyword).
template <const char *base, typename storage_t, typename T, int align = 0> class ArrayNearPtr
{
    IMPL(ArrayNearPtr)
};

// NearPtr against dynamic base store in a variable, for example, received
// from malloc().
template <char*& base, typename storage_t, typename T, int align = 0> class VarNearPtr
{
    IMPL(VarNearPtr)
};

#if 0
// Example usage:

const int base1 = 0x20000000;
char base2[256] = "foobar";
char *base3 = (char*)malloc(256);

template <typename T> using Ptr1 = AbsNearPtr<base1, uint16_t, T>;
template <typename T> using Ptr2 = ArrayNearPtr<base2, uint16_t, T>;
template <typename T> using Ptr3 = VarNearPtr<base3, uint16_t, T>;

Ptr2<char> p = &base2[3];
printf("%c", *p); // Produces "b"
#endif

#endif // _NEAR_PTR_HPP
