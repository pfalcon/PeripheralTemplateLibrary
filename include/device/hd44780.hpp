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
#include <gpio.hpp>
#include <signal.hpp>
#include <parallel_bus.hpp>

#define HD44780_CMD_CLS        0x01
#define HD44780_CMD_HOME       0x02
#define HD44780_CMD_ENTRY_MODE 0x04

// Display Features On/Off Control
#define HD44780_CMD_DISP_CTRL  0x08

// Shift cursor or display w/o changing content
#define HD44780_CMD_SHIFT      0x10

// Function set. p.27 "Perform the function at the head of the program
// before executing any instructions (except for the read busy flag and
// address instruction)."
#define HD44780_CMD_FUNC_SET   0x20
#define HD44780_CMD_SET_CGRAM  0x40
// p.29 "when N is 0 (1-line display), AAAAAAA can be 00H to 4FH. When N is 1 (2-line display),
// AAAAAAA can be 00H to 27H for the first line, and 40H to 67H for the second line.""
#define HD44780_CMD_SET_DDRAM  0x80

#define HD44780_ENTRY_CURSOR   0x00
#define HD44780_ENTRY_DISPLAY  0x01
#define HD44780_ENTRY_DEC      0x00
#define HD44780_ENTRY_INC      0x02

#define HD44780_SHIFT_CURSOR   0x00
#define HD44780_SHIFT_DISPLAY  0x08
#define HD44780_SHIFT_LEFT     0x00
#define HD44780_SHIFT_RIGHT    0x04

#define HD44780_CTRL_BLINK_ON  0x01
#define HD44780_CTRL_CURSOR_ON 0x02
#define HD44780_CTRL_DISP_ON   0x04

#define HD44780_FUNC_DL4       0x00
#define HD44780_FUNC_DL8       0x10
#define HD44780_FUNC_NLINES1   0x00
#define HD44780_FUNC_NLINES2   0x08
#define HD44780_FUNC_F5x8      0x00
#define HD44780_FUNC_F5x10     0x04


template < class delayer, class data4_bus, class en_sig, class regsel_sig, class rw_sig = Signal<NullPin> >
class HD44780
{
public:
    static void init(uint8_t params = HD44780_FUNC_NLINES2 | HD44780_FUNC_F5x8) {
        en_sig::deassert();
        data4_bus::output();
        write_cmd(HD44780_CMD_FUNC_SET | HD44780_FUNC_DL4 | params);
        cls();
    }

    static void cls() {
        write_cmd(HD44780_CMD_CLS);
        // p.24
        delayer::delay_us(1520);
    }

    static void home() {
        write_cmd(HD44780_CMD_HOME);
        // p.24
        delayer::delay_us(1520);
    }

    static void set_pos(uint8_t x, uint8_t y) {
        uint8_t addr = x;
        if (y > 0)
            addr += 0x40;
        write_cmd(HD44780_CMD_SET_DDRAM | addr);
        set_data_mode();
    }

    static void write_cmd(uint8_t val) {
        regsel_sig::deassert();
        rw_sig::deassert();
        write(val);
    }

    static void set_data_mode() {
        regsel_sig::assert();
    }

    static void write_data(uint8_t val) {
        set_data_mode();
        write(val);
    }

    static void write(uint8_t val) {
        // HD44780U datasheet p.22
        // As for the order of data transfer, the four high order bits (for 8-bit operation,
        // DB4 to DB7) are transferred before the four low order bits (for 8-bit operation, DB0 to DB3).
        write_4bits(val >> 4);
        write_4bits(val);
        // p.24: Any command (including data write) takes 37us,
        // so we delay here, in write(). For data write, there's
        // additional 4us delay (tADD, p.25) to update RAM pointer.
        delayer::delay_us(37 + 4);
    }

    static void write_4bits(uint8_t val) {
        data4_bus::write(val);
        // p.49 Data set-up time tDSW min 195ns
        pulse_en();
    }

    static uint8_t read() {
        rw_sig::assert();
        // HD44780U datasheet p.22
        // As for the order of data transfer, the four high order bits (for 8-bit operation,
        // DB4 to DB7) are transferred before the four low order bits (for 8-bit operation, DB0 to DB3).
        pulse_en();
        // p.49 Data delay time tDDR max 360ns
        uint8_t v = data4_bus::read() << 4;
        pulse_en();
        // p.49 Data delay time tDDR max 360ns
        v |= data4_bus::read();
        // Write is default
        rw_sig::deassert();
        // delay? p.25
    }

    static void pulse_en() {
        en_sig::assert();
        // p.49 Enable pulse width (high level) PWEH min 450ns
        delayer::delay_us(1);
        en_sig::deassert();
        // p.49 Enable cycle time tCycE min 1000ns
    }
};
