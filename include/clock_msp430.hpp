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
#include <msp430.h>
#include <legacymsp430.h>

#define SELS_0  0
#define SELS_1  SELS
#define XTS_0   0
#define XTS_1   XTS

enum ClockDivider { DIV_1, DIV_2, DIV_4, DIV_8 };

enum CrystalCapacitance { CAP_1pF = XCAP_0, CAP_6pF = XCAP_1, CAP_10pF = XCAP_2, CAP_12_5pF = XCAP_3 };

enum CrystalRange { /*TODO*/ };

// Internal very low power, low frequency oscillator
struct VLOCLK
{
    static uint8_t mclk()
    {
        return SELM_3;
    }

    static uint8_t smclk()
    {
        return SELS_1;
    }

    static uint8_t aclk_BCSCTL1()
    {
        // TI screwed up naming here
        return XTS_0;
    }

    static uint8_t aclk_BCSCTL3()
    {
        // TI screwed up naming here
        return LFXT1S_2;
    }
};

// Internal digitally controlled oscillator
class DCOCLK
{
    static void config(uint8_t range, uint8_t subfreq, uint8_t modulator)
    {
        DCOCTL = (subfreq << 5) | modulator;
    }
};


// Low-frequency/high-frequency external clock
template <enum CrystalCapacitance cap>
class LFXT1CLK_LO_CRYSTAL
{
    static uint8_t aclk()
    {
        // TI screwed up naming here
        return XTS_0 | LFXT1S_0 | (cap << 2);
    }
};

class LFXT1CLK_LO_EXTCLK
{
    static uint8_t aclk()
    {
        // TI screwed up naming here
        return XTS_0 | LFXT1S_3;
    }
};

template <enum CrystalRange range>
class LFXT1CLK_HI_CRYSTAL
{
    static uint8_t aclk()
    {
        // TI screwed up naming here
        return XTS_1 | (range << 4);
    }
};

class LFXT1CLK_HI_EXTCLK
{
    static uint8_t aclk()
    {
        // TI screwed up naming here
        return XTS_1 | LFXT1S_3;
    }
};


// Optional high-frequency external clock
class XT2CLK
{
    static void enable()
    {
        BCSCTL1 &= ~XT2OFF;
    }
    static void disable()
    {
        BCSCTL1 |= XT2OFF;
    }
};


class MCLK
{
//    static void source(enum ClockSource source);

    static uint16_t as_adc_clock()
    {
        return ADC10SSEL_2;
    }
};

class SMCLK
{
//    static void source(enum ClockSource source);

    static uint16_t as_timer_clock()
    {
        return TASSEL_2;
    }

    static uint16_t as_adc_clock()
    {
        return ADC10SSEL_3;
    }
};

struct ACLK
{
    template <class source_, enum ClockDivider div>
    static void source()
    {
        BCSCTL1 = BCSCTL1 & ~((3 << 4) | XTS) | (div << 4) | source_::aclk_BCSCTL1();
        BCSCTL3 = (BCSCTL3 & ~(LFXT1S_3 | XCAP_3)) | source_::aclk_BCSCTL3();
    }

    static uint16_t as_timer_clock()
    {
        return TASSEL_1;
    }

    static uint16_t as_adc_clock()
    {
        return ADC10SSEL_1;
    }
};
