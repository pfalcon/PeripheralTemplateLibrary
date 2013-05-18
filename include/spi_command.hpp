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
#ifndef _SPI_COMMAND_HPP
#define _SPI_COMMAND_HPP

#include <stdint.h>
#include <spi.hpp>

namespace PTL {

template <class spi, class cs>
class SPICommandMixIn
{
public:
    static void init()
    {
        cs::output();
        cs::deassert();
    }

    static uint8_t spi_command(uint8_t cmd)
    {
        uint8_t val;
        cs::assert();
        val = spi::transfer(cmd);
        cs::deassert();
        return val;
    }

    static uint8_t spi_command_read(uint8_t cmd)
    {
        uint8_t val;
        cs::assert();
        spi::transfer(cmd);
        val = spi::transfer(0xFF);
        cs::deassert();
        return val;
    }

    static void spi_command_write(uint8_t cmd, uint8_t val)
    {
        cs::assert();
        spi::transfer(cmd);
        spi::transfer(val);
        cs::deassert();
    }

    static void spi_command_read_block(uint8_t cmd, uint8_t *buf, uint8_t len)
    {
        cs::assert();
        spi::transfer(cmd);
        spi::read_block(buf, len);
        cs::deassert();
    }

    static void spi_command_write_block(uint8_t cmd, const uint8_t *buf, uint8_t len)
    {
        cs::assert();
        spi::transfer(cmd);
        spi::write_block(buf, len);
        cs::deassert();
    }
};

} // namespace

#endif //_SPI_COMMAND_HPP
