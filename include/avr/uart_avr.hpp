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
#ifndef _UART_AVR_HPP
#define _UART_AVR_HPP

#include <avr/cpu_avr.hpp>

#define DIVISOR(freq, baud, div) ((freq) / (div * (baud)) - 1)

template <unsigned long freq, unsigned long baud>
class UART<freq, baud, USART0>
{
public:
    static void init()
    {
        _R8(UCSR0C) = _BV(UCSZ01) | _BV(UCSZ00);
        if (DIVISOR(freq, baud, 16) > 15) {
            _R8(UCSR0A) = 0;
            _R16(UBRR0) = DIVISOR(freq, baud, 16);
        } else {
            _R8(UCSR0A) = _BV(U2X0);
            _R16(UBRR0) = DIVISOR(freq, baud, 8);
        }
        _R8(UCSR0B) = _BV(TXEN0) | _BV(RXEN0);
    }

    static uint8_t read()
    {
        while (!(_R8(UCSR0A) & _BV(RXC0)));
        return _R8(UDR0);
    }

    static void write(uint8_t b)
    {
        _R8(UDR0) = b;
        while (!(_R8(UCSR0A) & _BV(UDRE0)));
    }

    static uint8_t read_async()
    {
        return _R8(UDR0);
    }

    static void write_async(uint8_t b)
    {
        _R8(UDR0) = b;
    }

    static bool read_ready()
    {
        return _R8(UCSR0A) & _BV(RXC0);
    }

    static bool write_ready()
    {
        return _R8(UCSR0A) & _BV(UDRE0);
    }

    static void enable_rx_irq()  { _R8(UCSR0B) |= _BV(RXCIE0); }
    static void disable_rx_irq() { _R8(UCSR0B) &= ~_BV(RXCIE0); }
    static void enable_tx_irq()  { _R8(UCSR0B) |= _BV(UDRIE0); }
    static void disable_tx_irq() { _R8(UCSR0B) &= ~_BV(UDRIE0); }

//    static interrupt(USCIAB0RX_VECTOR) irq_handler_rx();
//    static interrupt(USCIAB0TX_VECTOR) irq_handler_tx();
};

#endif //_UART_AVR_HPP
