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
#ifndef _IRQ_DISPATCH_BASE_HPP
#define _IRQ_DISPATCH_BASE_HPP

namespace PTL {

/**
 ** Device-independent helper macros/classes for interrupt dispatching
 **/

/* Null MCU device block, used as a placeholder. */
class NullBlock
{
public:
    const static int block_type = 0;
};

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

} // namespace

#endif // _IRQ_DISPATCH_BASE_HPP
