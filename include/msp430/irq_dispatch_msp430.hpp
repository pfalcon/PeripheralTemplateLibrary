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

#include <msp430.h>
// interrupt(X) define. TODO: get rid of?
#include <legacymsp430.h>
#include <irq_dispatch_base.hpp>

namespace PTL {

/* Functions to dispatch specific hardware IRQ down to a specific 
   MCU block and its PTL irq events. */

IRQ_DISPATCH_HELPER(do_timer_main, block::block_type == MSP430_TIMER)
{
    // Reading status also acks IRQ
    switch (block::irq_status()) {
    // 1. MSP headers define TAIV bits per-timer, but they are actually
    // the same for all timers (hopefully for all MCUs!)
    // 2. Method calls below are expected to be inlined, and if
    // one is empry, entire branch to be dead-code elimated.
    case TA0IV_TAIFG:
        block::irq_reset();
        break;
    case TA0IV_TACCR1:
        block::irq_capture_compare1();
        break;
    case TA0IV_TACCR2:
        block::irq_capture_compare2();
        break;
    }
}

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

/* Class which encapsulates all hardware -> PTL dispatchers. Mostly
   used to allow variable list of blocks to dispatch to. */
template <class b1, class b2 = NullBlock, class b3 = NullBlock>
class IrqDispatch
{
public:
    HANDLER(TIMER0_A1_VECTOR, do_timer_main);
    HANDLER(TIMER0_A0_VECTOR, do_timer_cc0);
    HANDLER_CACHE_REG(USCIAB0RX_VECTOR, do_usci_rx, IFG2);
    HANDLER_CACHE_REG(USCIAB0TX_VECTOR, do_usci_tx, IFG2);
};


/* Dispatch IRQ from MCU and compiler specific "IRQ vector" function. This
   is expected to be fully optimized out by inlining.
   What to change when porting: name/attributes of function defined. */
#define CALL_HANDLER(dispatcher, vector) \
    interrupt(vector) vector##Handler() \
    { \
        dispatcher::vector##Handler(); \
    }

/* Global IRQ dispatch declaration macro - that's what user uses in the
   application code. Note that there can be at most one IRQ_DISPATCH
   per application. Specifying all irq-receiving classes at once allows
   to suffle/sort/group irq handlers to produce optimal code - that's
   what all functions/classes/macros above do actually.

   Note that gross effect of thsi macro will be definition of all
   listed interrupt handler vectors - even though unused ones will
   be empty (or contain rudimentary dispatching/acknowledge code).
   This is price of magic of having hardware details independent
   IRQ routing. It's unclear how to optimize this further (likely,
   assembler preprocessing needed). So, it may be considered as
   part of runtime support code: like it or not, need it or not,
   it's just there, live with it. Once again, if you don't use
   interrupts (and IRQ_DISPATCH), you won't have this overhead.

   What to change when porting: list of CALL_HANDLER calls. */
#define IRQ_DISPATCH(blocks...) \
    template class IrqDispatch<blocks>; \
    typedef IrqDispatch<blocks> _irq_dispatch; \
    CALL_HANDLER(_irq_dispatch, TIMER0_A1_VECTOR); \
    CALL_HANDLER(_irq_dispatch, TIMER0_A0_VECTOR); \
    CALL_HANDLER(_irq_dispatch, USCIAB0RX_VECTOR); \
    CALL_HANDLER(_irq_dispatch, USCIAB0TX_VECTOR);

} // namespace

#endif // _IRQ_DISPATCH_MSP430_HPP
