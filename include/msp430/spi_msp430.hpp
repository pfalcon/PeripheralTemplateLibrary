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
#ifndef _SPI_MSP430_HPP
#define _SPI_MSP430_HPP

#include <spi.hpp>
#include <msp430/cpu_msp430.hpp>

// Hardware USCI SPI pins (P1)
#define SCLK    BIT5
#define SDI     BIT7
#define SDO     BIT6

template <>
class SPI<USCI_B> : public ISPI, public SPIBlockXfer< SPI<USCI_B> >, public MSP430Block
{
public:
    typedef USCI_B usci;
    const static int block_type = MSP430_USCI;

    static void init()
    {
        UCB0CTL1 = UCSWRST;

        // SMCLK
        UCB0CTL1 = UCSWRST | UCSSEL_2;

        // Suitable polarity mode, master, 3-wire SPI, synchronous op
        UCB0CTL0 = UCCKPH | UCMSB | UCMST | UCMODE_0 | UCSYNC;

        // SPI clock = SMCLK / 1
        UCB0BR0 = 1;
        UCB0BR1 = 0;

        P1SEL |= SCLK | SDI | SDO;
        P1SEL2 |= SCLK | SDI | SDO;
        // Per MSP430 manual, direction of SCLK/MOSI/MISO is controlled
        // by USCI module itself
        UCB0CTL1 &= ~UCSWRST;
    }

    static void disable()
    {
        UCB0CTL1 = UCSWRST;
        P1SEL &= ~(SCLK | SDI | SDO);
        P1SEL2 &= ~(SCLK | SDI | SDO);
    }

#define NOP() asm("nop")
#define NOP8() { NOP(); NOP(); NOP(); NOP(); NOP(); NOP(); NOP(); NOP(); }

    static uint8_t transfer(uint8_t b)
    {
        UCB0TXBUF = b;
        // We know that transfer takes 8 cycles, so instead of (long) loop,
        // just use 8 nop's.
        // while (!(IFG2 & UCB0RXIFG));
        NOP8();
        return UCB0RXBUF;
    }

    static void write(uint8_t b) { transfer(b); }

    static void irq_rx() {}
    static void irq_tx() {}
};

#endif //_SPI_MSP430_HPP
