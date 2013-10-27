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
#ifndef _GPIODYN_MSP430_HPP
#define _GPIODYN_MSP430_HPP

#include <types.hpp>
#include <gpio_base.hpp>
#include <msp430.h>

namespace PTL {

struct DynaPort_Store {
    // msp430 SFR (including port) registers are located in
    // first 256 bytes of address space, plus there's movzx
    // instruction. So, we can optimize port base addres
    // storage to byte w/o any overhead.
    uint8_t base;

    DynaPort_Store(uint8_t port_no) {
        set(port_no);
    }

    void set(uint8_t port_no) {
        switch (port_no) {
        case 0:
            base = P1::base;
            break;
        case 1:
            base = P2::base;
            break;
        case 2:
            base = P3::base;
            break;
        }
    }
};

struct DynaPin_Store : DynaPort_Store {
    // Pin mask, named for consistency with Bit<>::value
    uint8_t value;

    DynaPin_Store(uint8_t port_no, uint8_t pin_no) {
        set(port_no, pin_no);
    }

    void set(uint8_t port_no, uint8_t pin_no) {
        DynaPort_Store::set(port_no);
        value = 1 << pin_no;
    }
};

template <DynaPort_Store& store>
class DynaPort : public IPort<uint8_t> {
public:
    static void enable() { store.base; }
};

template <DynaPin_Store& store>
class DynaPin : public IPin<DynaPin<store>, uint8_t> {
    static int in_reg(int base) { return base; }
    static int out_reg(int base) { return base + 1; }
    static int dir_reg(int base) { return base + 2; }
    static int ren_reg(int base) { return base == P3::base ? P3REN_ : base + 7; }

public:
    typedef DynaPort<store> port;

    static width value()
    {
        return _REG8(in_reg(store.base)) & store.value;
    }
    static void high()
    {
        _REG8(out_reg(store.base)) |= store.value;
    }
    static void low()
    {
        _REG8(out_reg(store.base)) &= ~store.value;
    }
    static void toggle()
    {
        _REG8(out_reg(store.base)) ^= store.value;
    }
    static void output()
    {
        _REG8(dir_reg(store.base)) |= store.value;
    }
    static void input()
    {
        _REG8(dir_reg(store.base)) &= ~store.value;
    }
    static void pulloff()
    {
        _REG8(ren_reg(store.base)) &= ~store.value;
    }
    static void pullup()
    {
        _REG8(ren_reg(store.base)) |= store.value;
        _REG8(out_reg(store.base)) |= store.value;
    }
    static void pulldown()
    {
        _REG8(ren_reg(store.base)) |= store.value;
        _REG8(out_reg(store.base)) &= ~store.value;
    }
};

} // namespace

#endif //_GPIODYN_MSP430_HPP
