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
#ifndef _TIMER_MSP430_DISPATCH_HPP
#define _TIMER_MSP430_DISPATCH_HPP

#include <timer_base.hpp>
// interrupt(X) define. TODO: get rid of?
#include <legacymsp430.h>

namespace PTL {

// We use approach of grouping IRQ handlers into struct TimerIrqsBase
// because this allows easier method inlining for pre-C+11 compiers,
// and (arguably?) less tricky (but multi-level) empty handler usage.
struct TimerIrqsBase {
    // Empty, unused methods expected to be eliminated with --gc-sections
    static void overflow() {}
    static void cc0() {}
    static void cc1() {}
    static void cc2() {}
};

template <class timer, class irq_handlers>
class TimerIrqDispatch
{

public:
    ALWAYS_INLINE static void handle_main() {
        // Reading status also acks IRQ
        switch (timer::irq_status()) {
        // 1. MSP headers define TAIV bits per-timer, but they are actually
        // the same for all timers (hopefully for all MCUs!)
        // 2. Method calls below are expected to be inlined, and if
        // one is empry, entire branch to be dead-code elimated.
        case TA0IV_TAIFG:
            irq_handlers::overflow();
            break;
        case TA0IV_TACCR1:
            irq_handlers::cc1();
            break;
        case TA0IV_TACCR2:
            irq_handlers::cc2();
            break;
        }
    }

    ALWAYS_INLINE static void handle_cc0() {
        irq_handlers::cc0();
    }

    // The idea would be to *define* *Timer's* irq_handler*() here (as a friend
    // method). Unfortunately that's not supported by C++. So, we'll define
    // irq handlers as ours, at least Timer::irq_no_* allows us to avoid duplication
    // and abstract it a bit.

    // Unfortunately, this doesn't work with gcc 4.5 either

#if 0
    static interrupt(Timer::irq_no_main) irq_handler()
    {
        handle_main();
    }

    static interrupt(Timer::irq_no_cc0) irq_handler_cc0()
    }
        if (cc0) cc0();
    }
#endif
};

// Can't get around using macros - see above
// But now that we need to use macros, let's hide TimerIrqDispatch
// instantiation there too.
#define IRQ_DISPATCH(timer, irq_handlers) \
    template <> \
    void timer::irq_handler() \
    { TimerIrqDispatch<timer, irq_handlers>::handle_main(); } \
    template <> \
    void timer::irq_handler_cc0() \
    { TimerIrqDispatch<timer, irq_handlers>::handle_cc0(); }

} // namespace

#endif // _TIMER_MSP430_DISPATCH_HPP
