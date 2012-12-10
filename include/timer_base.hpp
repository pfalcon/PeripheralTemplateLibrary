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
template <typename width_, class timer_impl>
class ITimer {
public:
    typedef width_ width;

    static bool expired(width start, width duration)
    {
        return timer_impl::value() - start >= duration;
    }

    static void delay(width cycles)
    {
        width start = timer_impl::value();
        delay_since(start, cycles);
    }

    static void delay(uint32_t cycles)
    {
        width start = timer_impl::value();
        while (true) {
            width end = timer_impl::value();
            cycles -= end - start;
            if ((int32_t)cycles < 0)
                break;
            start = end;
        }
    }

    static void delay_since(width since, width delay)
    {
        while (timer_impl::value() - since < delay);
    }
};
