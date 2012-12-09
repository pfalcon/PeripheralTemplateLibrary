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
#ifndef _SPI_BASE_HPP
#define _SPI_BASE_HPP

class ISPI
{
public:
    static void init();
    static uint8_t transfer(uint8_t b);
    // Optimized version of transfer which ignores read value
    static void write(uint8_t b);
};


template <class spi_impl>
class SPIBlockXfer
{
public:
    // Oftentimes, duplex SPI transfers are not used,
    // and instead separate read/write transactions
    // are used. Functions below allow for efficient
    // implementation of such, with basic default
    // implementation provided.
    static void read_block(uint8_t *buf, uint8_t len);
    static void write_block(const uint8_t *buf, uint8_t len);
};

template <class spi_impl>
void SPIBlockXfer<spi_impl>::read_block(uint8_t *buf, uint8_t len)
{
    while (len--) {
        *buf++ = spi_impl::transfer(0xFF);
    }
}

template <class spi_impl>
void SPIBlockXfer<spi_impl>::write_block(const uint8_t *buf, uint8_t len)
{
    while (len--) {
         spi_impl::write(*buf++);
    }
}

#endif //_SPI_BASE_HPP
