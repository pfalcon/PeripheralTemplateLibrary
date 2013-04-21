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

class CSysTick : public ITimer<CSysTick, COUNT_DOWN, uint32_t, 24>
{
public:
    typedef uint32_t width;

    static width value() { return SysTick->VAL; }
    static void free_run()
    {
        SysTick->LOAD = 0xffffff;
        SysTick->CTRL |= SysTick_CTRL_ENABLE;
    }

    static void enable_irq()  { SysTick->CTRL |= SysTick_CTRL_TICKINT; }
    static void disable_irq() { SysTick->CTRL &= ~SysTick_CTRL_TICKINT; }
};

typedef CSysTick timer;

#endif // _TIMER_CORTEXM_SYSTICK_HPP
