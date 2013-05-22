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
#ifndef _SLEEP_MSP430_HPP
#define _SLEEP_MSP430_HPP

#include <stdlib.h>
#include <stdio.h>

namespace PTL {

class Sleep
{
public:
    static void sleep(uint32_t interval)
    {
        usleep(interval);
    }

    static void powerdown()
    {
        fprintf(stderr, "System powered down\n");
        exit(99);
    }
};

} // namespace

#endif //_SLEEP_MSP430_HPP
