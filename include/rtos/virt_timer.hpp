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
#ifndef _VIRT_TIMER_HPP
#define _VIRT_TIMER_HPP

#include <timer.hpp>

namespace PTL {

template <class timer>
class VirtTimer
{
    typename timer::width start;
    typename timer::width period;
public:
    void start(typename timer::width period) { start = timer::value(); this->period = period; }
    bool expired()
      { return timer::elapsed(timer::value(), start) > period; }
};

} // namespace

#endif //_VIRT_TIMER_HPP
