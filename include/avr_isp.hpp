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
#include <spi.hpp>

namespace PTL {

template <class delayer, class spi, class reset_sig>
class AVR_ISP
{
public:
    static void init()
    {
        reset_sig::output();
        reset_sig::deassert();
    }

    static void start()
    {
        reset_sig::assert();
        //AVR910
        delayer::delay_ms(20);
    }

    static void send_cmd(uint16_t cmd, uint8_t b2, uint8_t b3)
    {
        spi::transfer(cmd >> 8);
        spi::transfer(cmd & 0xff);
        spi::transfer(b2);
        return spi::transfer(b3);
    }

    static void enable_program()
    {
        if (send_cmd(CMD_Program_Enable, 0x55, 0xaa) != 0x55)
            return false;
        return true;
    }

    static void read_flash(uint16_t addr)
    {
        uint16_t cmd = addr & 1 ? CMD_Read_Flash_High : CMD_Read_Flash_Low;
        addr >>= 1;
        return send_cmd(cmd | (addr >> 8), addr & 0xff, 0);
    }
};

} // namespace
