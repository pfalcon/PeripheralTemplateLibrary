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

// C++ metaprogramming helper

#include <stdint.h>

namespace meta {

// enable_if
template <bool B, class T = void>
struct enable_if {};
template <class T>
struct enable_if<true, T> { typedef T type; };

// signed_t
template <typename T> struct signed_t {};
template <> struct signed_t<uint8_t>  { typedef int8_t type; };
template <> struct signed_t<uint16_t> { typedef int16_t type; };
template <> struct signed_t<uint32_t> { typedef int32_t type; };
template <> struct signed_t<uint64_t> { typedef int64_t type; };

};
