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

#include <types.hpp>
#include <gpio.hpp>

namespace PTL {

class ISPI
{
public:
    static void init();
    static uint8_t transfer(uint8_t b);
    // Optimized version of transfer which uses arbitrary write value
    static uint8_t read();
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
    static void read_block(uint8_t *buf, uint8_t len)
    {
        while (len--) {
            *buf++ = spi_impl::read();
        }
    }

    static void write_block(const uint8_t *buf, uint8_t len)
    {
        while (len--) {
             spi_impl::write(*buf++);
        }
    }
};


template <class sclk, class miso = None, class mosi = None>
class SPI : public ISPI, public SPIBlockXfer< SPI<sclk, miso, mosi> >
{
public:
    static void init()
    {
        sclk::output();
        mosi::output();
        miso::input();
    }
    static uint8_t transfer(uint8_t b);
    static uint8_t read();
    static void write(uint8_t b);

};

template <class sclk, class miso, class mosi>
uint8_t SPI<sclk, miso, mosi>::transfer(uint8_t b)
{
        for (uint8_t i = 8; i; i--) {
            if (b & 0x80)
                mosi::high();
            else
                mosi::low();

            sclk::high();

            b <<= 1;

            if (miso::value())
                b |= 1;

            sclk::low();
        }
        return b;
}

template <class sclk, class miso, class mosi>
void SPI<sclk, miso, mosi>::write(uint8_t b)
{
        for (uint8_t i = 8; i; i--) {
            if (b & 0x80)
                mosi::high();
            else
                mosi::low();

            sclk::high();

            b <<= 1;

            sclk::low();
        }
}

template <class sclk, class miso, class mosi>
uint8_t SPI<sclk, miso, mosi>::read()
{
    // TODO: optimize
    return transfer(0xFF);
}

} // namespace

#endif //_SPI_BASE_HPP
