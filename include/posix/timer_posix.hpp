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
#ifndef _TIMER_POSIX_HPP
#define _TIMER_POSIX_HPP

#include <sys/time.h>

#include <timer_base.hpp>

namespace PTL {

class Timer : public ITimer<Timer, COUNT_UP, uint32_t>
{
public:

    static width value()
    {
        struct timeval t;
        gettimeofday(&t, NULL);
        return t.tv_sec * 1000000 + t.tv_usec;
    }

    static void free_run()
    {
        // Always running
    }
};

typedef Timer timer;

} // namespace

#endif // _TIMER_POSIX_HPP
