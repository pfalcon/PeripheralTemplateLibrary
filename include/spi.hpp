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
#ifndef _SPI_HPP
#define _SPI_HPP

#include <types.hpp>
#include <spi_base.hpp>
#include <gpio.hpp>

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

#endif //_SPI_HPP
