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
#include <timer_base.hpp>
// interrupt(X) define. TODO: get rid of?
#include <legacymsp430.h>

template <int ctrl_reg_, int val_reg_, int intr_reg_>
class Timer : public ITimer<uint16_t>
{
public:
    static const int ctrl_reg = ctrl_reg_;
    static const int val_reg = val_reg_;
    static const int intr_reg = intr_reg_;

    static width value() { return *(volatile width*)val_reg; }
    static void free_run();

    static bool expired(width start, width duration)
    {
        return value() - start >= duration;
    }

    static void delay(width cycles)
    {
        width start = value();
        delay_since(start, cycles);
    }

    static void delay(uint32_t cycles)
    {
        width start = value();
        while (true) {
            width end = value();
            cycles -= end - start;
            if ((int32_t)cycles < 0)
                break;
            start = end;
        }
    }

    static void delay_since(width since, width delay)
    {
        while (value() - since < delay);
    }

    static void enable_irq()  { *(volatile uint16_t*)ctrl_reg |= TAIE; }
    static void disable_irq() { *(volatile uint16_t*)ctrl_reg &= ~TAIE; }
//    __attribute__((interrupt(TIMER0_A1_VECTOR))) static void irq_handler();
    interrupt(TIMER0_A1_VECTOR) irq_handler();
};

template <int ctrl_reg_, int val_reg_, int intr_reg_>
void Timer<ctrl_reg_, val_reg_, intr_reg_>::free_run()
{
    // SMCLK, continuous mode
    TACTL = TASSEL_2 | MC_2;
}

typedef Timer<TACTL_, TAR_, TAIV_> Timer0_A;
#ifdef TA1CTL_
typedef Timer<TACTL_, TAR_, TAIV_> Timer1_A;
#endif
typedef Timer0_A timer;
