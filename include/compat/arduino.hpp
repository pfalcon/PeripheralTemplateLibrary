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

/* Arduino compatibility header, which allows to compile arduino code
   minimal code logic changes (but no so minimal declarations changes). */

#define ARDUINO 101

#define LOW 0
#define HIGH 1
#define INPUT 0
#define OUTPUT 1
#define LSBFIRST 0
#define MSBFIRST 1

#define digitalWrite(pin, val) pin::set(val)

template<class pin, bool mode>
inline void _pinMode()
{
    if (mode == OUTPUT)
        pin::output();
    else
        pin::input();
}
#define pinMode(pin, mode) _pinMode<pin, mode>()

template<class pin_data, class pin_clk, bool msbfirst>
void _shiftOut(uint8_t b)
{
    if (msbfirst == MSBFIRST) {
        // from SPI::write
        for (uint8_t i = 8; i; i--) {
            if (b & 0x80)
                pin_data::high();
            else
                pin_data::low();

            pin_clk::high();

            b <<= 1;

            pin_clk::low();
        }
    } else {
        for (uint8_t i = 8; i; i--) {
            if (b & 0x01)
                pin_data::high();
            else
                pin_data::low();

            pin_clk::high();

            b >>= 1;

            pin_clk::low();
        }
    }
}
#define shiftOut(pin_data, pin_clk, msbfirst, data) _shiftOut<pin_data, pin_clk, msbfirst>(data)

#define delay(n) delayer::delay_ms(n)
