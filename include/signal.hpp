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
#ifndef _SIGNAL_HPP
#define _SIGNAL_HPP

namespace PTL {

template <class pin>
class Signal
{
public:
    typedef typename pin::port port;

    static void output()   { pin::output(); }
    static void input()    { pin::input(); }
    static void assert()   { pin::high(); }
    static void deassert() { pin::low(); }
    static void toggle()   { pin::toggle(); }
    static bool value()    { return pin::value(); }
    static bool is_asserted()    { return value(); }
};

template <class pin>
class InvertedSignal
{
public:
    typedef typename pin::port port;

    static void output()   { pin::output(); }
    static void input()    { pin::input(); }
    static void assert()   { pin::low(); }
    static void deassert() { pin::high(); }
    static void toggle()   { pin::toggle(); }
    static bool value()    { return !pin::value(); }
    static bool is_asserted()    { return value(); }
};

} // namespace

#endif //_SIGNAL_HPP

