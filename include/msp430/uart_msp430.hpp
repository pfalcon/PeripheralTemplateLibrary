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
#ifndef _UART_MSP430_HPP
#define _UART_MSP430_HPP

#include <msp430/cpu_msp430.hpp>

template <unsigned long freq, unsigned long baud>
class UART<freq, baud, USCI>
{
public:
    static void init()
    {
        /*
        slau144i.pdf 15.3.1 p.424
The recommended USCI initialization/re-configuration process is:
1. Set UCSWRST (BIS.B #UCSWRST,&UCAxCTL1)
2. Initialize all USCI registers with UCSWRST = 1 (including UCAxCTL1)
3. Configure ports.
4. Clear UCSWRST via software (BIC.B #UCSWRST,&UCAxCTL1)
5. Enable interrupts (optional) via UCAxRXIE and/or UCAxTXIE
        */
        UCA0CTL1 |= UCSWRST;
        UCA0CTL0 = UCMODE_0;
        UCA0CTL1 = UCSSEL_2 | UCSWRST;
        UCA0BR0 = (freq / baud) & 0xff;
        UCA0BR1 = (freq / baud) >> 8;
        //uint8_t mod = (freq * 8 / baud) - (freq / baud * 8);
        // Proper rounding
        uint8_t mod = ((freq * 8 * 2 / baud) - (freq / baud * 8 * 2) + 1) / 2;
        UCA0MCTL = mod << 1;
        P1SEL |= BIT1 | BIT2;
        P1SEL2 |= BIT1 | BIT2;
        P1DIR &= ~BIT1;
        P1DIR |= BIT2;
        UCA0CTL1 &= ~UCSWRST;
    }

    static uint8_t read()
    {
        while (!(IFG2 & UCA0RXIFG));
        return UCA0RXBUF;
    }

    static void write(uint8_t b)
    {
        UCA0TXBUF = b;
        while (!(IFG2 & UCA0TXIFG));
    }

    static uint8_t read_async()
    {
        return UCA0RXBUF;
    }

    static void write_async(uint8_t b)
    {
        UCA0TXBUF = b;
    }

    static bool read_ready()
    {
        return IFG2 & UCA0RXIFG;
    }

    static bool write_ready()
    {
        return IFG2 & UCA0TXIFG;
    }

    static void enable_rx_irq()  { IE2 |= UCA0RXIE; }
    static void disable_rx_irq() { IE2 &= ~UCA0RXIE; }
    static void enable_tx_irq()  { IE2 |= UCA0TXIE; }
    static void disable_tx_irq() { IE2 &= ~UCA0TXIE; }

    static interrupt(USCIAB0RX_VECTOR) uart_rx_irq_handler();
    static interrupt(USCIAB0TX_VECTOR) uart_tx_irq_handler();
};

#endif //_UART_MSP430_HPP
