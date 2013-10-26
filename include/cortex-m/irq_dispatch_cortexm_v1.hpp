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
#ifndef _IRQ_DISPATCH_MSP430_HPP
#define _IRQ_DISPATCH_MSP430_HPP

namespace PTL {

class NullBlock
{
public:
    const static int block_type = 0;
};

/*
 * We want to declare a function here whose body will be executed only
 * when condition is true. We have to use metaprog conditionals here,
 * because if condition is false, func body may not compile at all
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


#if 0
IRQ_DISPATCH_HELPER(do_timer_cc0, block::block_type == MSP430_TIMER)
{
    block::irq_capture_compare0();
}

IRQ_DISPATCH_HELPER(do_usci_rx, block::block_type == MSP430_USCI)
{
    uint8_t ifg2 = val;
    if (block::usci::no == 'A' && (ifg2 & UCA0RXIFG))
        block::irq_rx();

    if (block::usci::no == 'B' && (ifg2 & UCB0RXIFG))
        block::irq_rx();
}

IRQ_DISPATCH_HELPER(do_usci_tx, block::block_type == MSP430_USCI)
{
    uint8_t ifg2 = val;
    if (block::usci::no == 'A' && (ifg2 & UCA0TXIFG))
        block::irq_tx();

    if (block::usci::no == 'B' && (ifg2 & UCB0TXIFG))
        block::irq_tx();
}
#endif

#define APPLY_TO_ALL(func, b1, b2, b3) { func<b1>(); func<b2>(); func<b3>(); }
#define APPLY_TO_ALL_ARG(func, arg, b1, b2, b3) { func<b1>(arg); func<b2>(arg); func<b3>(arg); }

#if 0
#define HANDLER(vector, dispatch_func) \
    static interrupt(vector) vector##_handler() \
    { \
        APPLY_TO_ALL(dispatch_func, b1, b2, b3); \
    }

#define HANDLER_CACHE_REG(vector, dispatch_func, reg) \
    static interrupt(vector) vector##_handler() \
    { \
        uint8_t cache = reg; \
        APPLY_TO_ALL_ARG(dispatch_func, cache, b1, b2, b3); \
    }

template <class b1, class b2 = NullBlock, class b3 = NullBlock>
class IrqDispatch
{
public:
    HANDLER(TIMER0_A1_VECTOR, do_timer_main);
    HANDLER(TIMER0_A0_VECTOR, do_timer_cc0);
    HANDLER_CACHE_REG(USCIAB0RX_VECTOR, do_usci_rx, IFG2);
    HANDLER_CACHE_REG(USCIAB0TX_VECTOR, do_usci_tx, IFG2);
};
#endif


#define HANDLER(vector, dispatch_func, blocks...) \
    void vector##Handler() \
    { \
        APPLY_TO_ALL(dispatch_func, blocks); \
    }


IRQ_DISPATCH_HELPER(do_systick, block::block_type == CORTEXM_SYSTICK)
{
    block::irq_reset();
}

#define IRQ_DISPATCH(blocks...) \
    HANDLER(SysTick_, do_systick, blocks);


} // namespace

#endif // _IRQ_DISPATCH_MSP430_HPP
