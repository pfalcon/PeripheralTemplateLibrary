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
#ifndef _TIMER_MSP430_HPP
#define _TIMER_MSP430_HPP

#include <timer_base.hpp>
// interrupt(X) define. TODO: get rid of?
#include <legacymsp430.h>

template <int ctrl_reg_, int val_reg_, int intr_reg_>
class Timer : public ITimer< Timer<ctrl_reg_, val_reg_, intr_reg_>, COUNT_UP, uint16_t >
{
public:
    typedef uint16_t width;

    static const int ctrl_reg = ctrl_reg_;
    static const int val_reg = val_reg_;
    static const int intr_reg = intr_reg_;
    // TODO: refactor into common clock infra
    enum ClockDivider { DIV_1 = ID_0, DIV_2 = ID_1, DIV_4 = ID_2, DIV_8 = ID_3 };

    static width value() { return *(volatile width*)val_reg; }
    static void free_run(ClockDivider div = DIV_1)
    {
        // SMCLK, continuous mode
        _REG16(ctrl_reg) = TASSEL_2 | MC_2 | div;
    }

    static void enable_irq()  { *(volatile uint16_t*)ctrl_reg |= TAIE; }
    static void disable_irq() { *(volatile uint16_t*)ctrl_reg &= ~TAIE; }
    static uint16_t irq_status() { return *(volatile uint16_t*)intr_reg; }
//    __attribute__((interrupt(TIMER0_A1_VECTOR))) static void irq_handler();
    static interrupt(TIMER0_A1_VECTOR) irq_handler();
    static interrupt(TIMER0_A0_VECTOR) irq_handler_cc0();
};


typedef Timer<TACTL_, TAR_, TAIV_> Timer0_A;
#ifdef TA1CTL_
typedef Timer<TA1CTL_, TA1R_, TA1IV_> Timer1_A;
#endif
typedef Timer0_A timer;

#endif // _TIMER_MSP430_HPP
