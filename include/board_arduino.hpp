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
#include <board_base.hpp>
#include <gpio.hpp>
#include <clock.hpp>
#include <timer.hpp>
#include <uart.hpp>

namespace PTL {

class Arduino {};

template <>
class Board<Arduino>
{
public:
    static const long freq = 16 MHZ;

    // "digital pin 13"
    typedef Pin<PB, Bit5> LED;
    // "digital pin 0"
    typedef Pin<PD, Bit0> pin_uart_rx;
    // "digital pin 1"
    typedef Pin<PD, Bit1> pin_uart_tx;
    //typedef UART<freq, 9600, pin_uart_tx, pin_uart_rx, timer> uart;
    typedef UART<freq, 115200, USART0> uart;

    // Arduino pin naming
    typedef Pin<PD, Bit0> D0;
    typedef Pin<PD, Bit1> D1;
    typedef Pin<PD, Bit2> D2;
    typedef Pin<PD, Bit3> D3;
    typedef Pin<PD, Bit4> D4;
    typedef Pin<PD, Bit5> D5;
    typedef Pin<PD, Bit6> D6;
    typedef Pin<PD, Bit7> D7;

    typedef Pin<PB, Bit0> D8;
    typedef Pin<PB, Bit1> D9;
    typedef Pin<PB, Bit2> D10;
    typedef Pin<PB, Bit3> D11;
    typedef Pin<PB, Bit4> D12;
    typedef Pin<PB, Bit5> D13;

    typedef Pin<PC, Bit0> A0;
    typedef Pin<PC, Bit1> A1;
    typedef Pin<PC, Bit2> A2;
    typedef Pin<PC, Bit3> A3;
    typedef Pin<PC, Bit4> A4;
    typedef Pin<PC, Bit5> A5;
};

typedef Board<Arduino> board;

} // namespace
