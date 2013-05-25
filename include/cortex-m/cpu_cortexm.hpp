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
#include <cortex-m/includes_cortexm.hpp>
#include <cpu_base.hpp>
// Declare Cortex-M IRQ handlers
#include <cortexm_irqs.h>

namespace PTL {

class CortexMCPU {};

template <>
class CPU<CortexMCPU> : public ICPU
{
public:
    static void init(int flags)
    {
        // CMSIS: The Startup File startup_<device>.s is executed
        // after reset and calls SystemInit().
    }

    static void enable_irq()  { __enable_irq(); }
    static void disable_irq() { __disable_irq(); }
};

} // namespace
