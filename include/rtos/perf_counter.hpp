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
#ifndef _PERF_COUNTER_HPP
#define _PERF_COUNTER_HPP

#include <timer.hpp>

namespace PTL {

#ifdef __MSP430__
#define PERF_COUNTER_CORRECTION 6
#else
#define PERF_COUNTER_CORRECTION 0
#endif

template <class timer>
class PerfCounter
{
    typename timer::width counter;
public:
    void start() { counter = timer::value(); }

    typename timer::width elapsed()
      { return timer::elapsed(timer::value(), counter) - PERF_COUNTER_CORRECTION; }

    typename timer::width stop()
      { return counter = elapsed(); }
    typename timer::width value()  { return counter; }
};

typedef PerfCounter<timer> Perf;

} // namespace

#endif //_PERF_COUNTER_HPP
