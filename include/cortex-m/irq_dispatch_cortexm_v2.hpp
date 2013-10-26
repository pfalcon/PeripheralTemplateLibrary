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

namespace PTL {

class NullBlock
{
public:
    const static int block_type = 0;
};

/**
 ** Device-independent helper macros for interrupt dispatching
 **/

/*
 * We want to declare a function whose body will be executed only
 * when (static) condition is true. We have to use metaprog conditionals
 * here, because if condition is false, func body may not compile at all
 * (for example because class it opeartes on lacks specific methods).
 * So, we use 2 complementary implementations of func: one with empty
 * body for case of condition == false, and one with the given body
 * in case it's true. All is wrapped with macros for readability.
 */

#define IRQ_DISPATCH_HELPER(func_name, cond) \
template <class block> \
inline void func_name(uint8_t val = 0, typename meta::enable_if<(!(cond))>::type* = 0) {} \
\
template <class block> \
inline void func_name(uint8_t val = 0, typename meta::enable_if<(cond)>::type* = 0) \

/* Apply templated function to list of template args. Note: this and other similar
   funcs depend on particular number of arguments passed and must be updated to
   pass more. */
#define APPLY_TO_ALL(func, b1, b2, b3) { func<b1>(); func<b2>(); func<b3>(); }
/* Apply templated function to list of template args, also passing (runtime) argument
   to a function. */
#define APPLY_TO_ALL_ARG(func, arg, b1, b2, b3) { func<b1>(arg); func<b2>(arg); func<b3>(arg); }

/* Define handler function for particular hardware IRQ. */
#define HANDLER(vector, dispatch_func) \
    static void vector##Handler() \
    { \
        APPLY_TO_ALL(dispatch_func, b1, b2, b3); \
    }

/* Define handler function for particular hardware IRQ, caching value
   of a register allowing to demux multiplexed IRQs. This cached value
   is passed to each PTL handler. */
#define HANDLER_CACHE_REG(vector, dispatch_func, reg) \
    static void vector##Handler() \
    { \
        uint8_t cache = reg; \
        APPLY_TO_ALL_ARG(dispatch_func, cache, b1, b2, b3); \
    }

/**
 ** Device-specific classes and macros for interrupt dispatching
 **/

/* Dispatch IRQ from MCU and compiler specific "IRQ vector" function. This
   is expected to be fully optimized out by inlining.
   What to change: name/attributes of function defined. */
#define CALL_HANDLER(dispatcher, vector) \
    void vector##Handler() \
    { \
        dispatcher::vector##Handler(); \
    }

/* Implementation of function which will dispatch harware IRQ to all
   blocks which have corresponding PTL handler.
   What to change: name, condition, implementation. */
IRQ_DISPATCH_HELPER(do_systick, block::block_type == CORTEXM_SYSTICK)
{
    block::irq_reset();
}

/* Main IRQ dispatching class. User needs to instantiate this per
   application needs (using explicit template instantiation). */
template <class b1, class b2 = NullBlock, class b3 = NullBlock>
class IrqDispatch
{
public:
    HANDLER(SysTick_, do_systick);
};

/* Macros to dispatch from MCU/compiler specific "IRQ vector function"
   to IrqDispatch class. The latter should be passed in as a param. */
#define IRQ_DISPATCH(dispatcher) \
    CALL_HANDLER(dispatcher, SysTick_);

/* Usage example: */
#if 0

class mytimer : public timer
{
public:
    void irq_reset()
    {
        // Do something
    }
};

// Don't Repeat Yourself, and explicit template instantiation cannot
// be applied to a typedef name, so user old trusty defines.
#define irq_dispatch IrqDispatch<mytimer>
template class irq_dispatch;
IRQ_DISPATCH(irq_dispatch);

#endif


} // namespace

#endif // _IRQ_DISPATCH_CORTEXM_HPP
