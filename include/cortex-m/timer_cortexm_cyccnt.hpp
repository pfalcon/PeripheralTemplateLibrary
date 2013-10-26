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
#ifndef _TIMER_CORTEXM_SYSTICK_HPP
#define _TIMER_CORTEXM_SYSTICK_HPP

#include <timer_base.hpp>

namespace PTL {

class CCycCnt : public ITimer<CCycCnt, COUNT_UP, uint32_t>
{
public:
    typedef uint32_t width;

    static width value() { return DWT->CYCCNT; }
    static void free_run()
    {
        // p.11-19 Cortex-M3 r2p0 TechRefMan
        // The TRCENA bit of the Debug Exception and Monitor Control Register must be set
        // before you can use the DWT.
        CoreDebug->DEMCR |= CoreDebug_DEMCR_TRCENA;
        if (DWT->CTRL == 0 || (DWT->CTRL & DWT_CTRL_NOCYCCNT)) {
            abort();
        }
        DWT->CTRL |= DWT_CTRL_CYCCNTENA;
    }
};

} // namespace

#endif // _TIMER_CORTEXM_SYSTICK_HPP
