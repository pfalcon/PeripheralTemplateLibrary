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
#ifndef _UART_LM4_HPP
#define _UART_LM4_HPP

#include <gpio.hpp>

class UART0_ {};

#define FRACT_PART(x) ((x) - ((long)(x)))


template <unsigned long freq, unsigned baud>
class UART<freq, baud, UART0_>
{
    typedef Pin<PA, Bit0> rxpin;
    typedef Pin<PA, Bit1> txpin;

public:
    static void init()
    {
        SYSCTL->RCGCUART |= Bit0::value;
        txpin::port::enable();
        // Both pins always belong to same port
        //rxpin::port::enable();
        rxpin::altfunc(1);
        txpin::altfunc(1);
        // No need to set pin direction, just enable
        rxpin::enable();
        txpin::enable();
        // 16 assumes UART->CR & HSE == 0
        UART0->CR &= ~UART_CR_UARTEN;
        UART0->IBRD = freq / (16 * baud);
        UART0->FBRD = int(FRACT_PART((double)freq / (16 * baud)) * 64 + 0.5);
        UART0->LCRH = UART_LCRH_WLEN_8;
        UART0->CC = UART_CC_CS_PIOSC;
        UART0->CR |= UART_CR_UARTEN | UART_CR_RXE | UART_CR_TXE;
    }

    static uint8_t read()
    {
        while (UART0->FR & UART_FR_RXFE);
        return UART0->DR;
    }

    static void write(uint8_t b)
    {
        UART0->DR = b;
        while (UART0->FR & UART_FR_TXFF);
    }

    static uint8_t read_async()
    {
        return UART0->DR;
    }

    static void write_async(uint8_t b)
    {
        UART0->DR = b;
    }

    static bool read_ready()
    {
        return !(UART0->FR & UART_FR_RXFE);
    }

    static bool write_ready()
    {
        return !(UART0->FR & UART_FR_TXFF);
    }

};

#endif //_UART_LM4_HPP
