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
#ifndef _IRQ_DISPATCH_CORTEXM_HPP
#define _IRQ_DISPATCH_CORTEXM_HPP

#include <irq_dispatch_base.hpp>

namespace PTL {

/**
 ** Device-specific classes and macros for interrupt dispatching
 **/

/* Implementation of function which will dispatch harware IRQ to all
   blocks which have corresponding PTL handler.
   What to change: name, condition, implementation. */
IRQ_DISPATCH_HELPER(do_systick, block::block_type == CORTEXM_SYSTICK)
{
    block::irq_reset();
}

/* Class which encapsulates all hardware -> PTL dispatchers. Mostly
   used to allow variable list of blocks to dispatch to. */
template <class b1, class b2 = NullBlock, class b3 = NullBlock>
class IrqDispatch
{
public:
    HANDLER(SysTick_, do_systick);
};

/* Dispatch IRQ from MCU and compiler specific "IRQ vector" function. This
   is expected to be fully optimized out by inlining.
   What to change: name/attributes of function defined. */
#define CALL_HANDLER(dispatcher, vector) \
    void vector##Handler() \
    { \
        dispatcher::vector##Handler(); \
    }

/* Macros to dispatch from MCU/compiler specific "IRQ vector function"
   to IrqDispatch class. The latter should be passed in as a param. */
#define IRQ_DISPATCH(blocks...) \
    template class IrqDispatch<blocks>; \
    typedef IrqDispatch<blocks> _irq_dispatch; \
    CALL_HANDLER(_irq_dispatch, SysTick_);


} // namespace

#endif // _IRQ_DISPATCH_CORTEXM_HPP
