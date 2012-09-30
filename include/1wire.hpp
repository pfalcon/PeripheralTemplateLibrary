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
#include "gpio.hpp"

// Reference: DS18B20 datasheet

template <class pin, class delayer>
class OneWire
{
public:
    static void init()
    {
        bus_release();
    }
    static void bus_low()
    {
        pin::output();
        pin::low();
    }
    static void bus_release()
    {
        pin::input();
        pin::pullup();
    }
    static void bus_power()
    {
        pin::pulloff(); // Required for MSP430
        pin::output();
        pin::high();
    }
    static typename pin::port::width bus_value()
    {
        return pin::value();
    }
    static void delay(int us)
    {
        delayer::delay(us * 8);
    }

    static bool reset();
    static void write0();
    static void write1();
    static typename pin::port::width read_bit();

    static void write(uint8_t b);
    static uint8_t read();
    static void read_block(uint8_t *buf, uint8_t len);
};

template <class pin, class delayer>
bool OneWire<pin, delayer>::reset()
{
    bus_low();
    delay(480);
    bus_release();
    delay(60);
    if (bus_value())
        return false;
    delay(250); // "presence pulse 60-240uS"
    if (!bus_value())
        return false;
    delay(170); // "master Rx 480uS minimum", 480 - (60 + 250)
    return true;
}

template <class pin, class delayer>
void OneWire<pin, delayer>::write0()
{
    bus_low();
    delay(60);
    bus_release();
    // Recovery
    delay(2);
}

template <class pin, class delayer>
void OneWire<pin, delayer>::write1()
{
    bus_low();
    delay(8);
    bus_release();
    delay(52);
    // Recovery
    delay(2);
}

template <class pin, class delayer>
typename pin::port::width OneWire<pin, delayer>::read_bit()
{
    bus_low();
    delay(5);
    bus_release();
    delay(8); // "the master must release the bus and then sample the bus state within 15us from the start of the slot."
    typename pin::port::width val = bus_value();
    delay(47);
    // Recovery
    delay(2);
    return val;
}

template <class pin, class delayer>
void OneWire<pin, delayer>::write(uint8_t b)
{
    for (int i = 8; i; i--) {
        if (b & 1)
            write1();
        else
            write0();
        b >>= 1;
    }
}

template <class pin, class delayer>
uint8_t OneWire<pin, delayer>::read()
{
    uint8_t b = 0;
    for (int i = 8; i; i--) {
        b >>= 1;
        if (read_bit())
            b |= 0x80;
    }
    return b;
}

template <class pin, class delayer>
void OneWire<pin, delayer>::read_block(uint8_t *buf, uint8_t len)
{
    while (len--) {
        *buf++ = read();
    }
}
