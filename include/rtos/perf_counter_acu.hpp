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
#ifndef _PERF_COUNTER_ACU_HPP
#define _PERF_COUNTER_ACU_HPP

#include <timer.hpp>

template <class timer, typename width_ = uint32_t>
class PerfCounterAcu
{
    width_ counter;
    typename timer::width last_val;
public:
    PerfCounterAcu() : counter(0) {}
    void reset() { counter = 0; }
    void start() { last_val = timer::value(); }
    void update()
    {
        typename timer::width t = timer::value();
        counter += timer::elapsed(t, last_val);
        last_val = t;
    }
    width_ value() { return counter; }
};

typedef PerfCounterAcu<timer> PerfAcu;

#endif //_PERF_COUNTER_ACU_HPP
