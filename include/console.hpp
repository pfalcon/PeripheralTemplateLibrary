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
#ifndef _CONSOLE_HPP
#define _CONSOLE_HPP

#include <stdarg.h>
#include <inline.hpp>

#define ENDL "\r\n"

template <class byte_writer>
class Console
{
public:
    void print_byte(uint8_t)
    {
    }

    static void newline()
    {
        byte_writer::write('\r');
        byte_writer::write('\n');
    }

    static void putc(uint8_t c)
    {
        byte_writer::write(c);
    }

    NOINLINE static void putstr(const char *str)
    {
        while (*str)
            putc(*str++);
    }

    static void puthex4(uint8_t b)
    {
        b += '0';
        if (b > '9')
            b += 7;
        byte_writer::write(b);
    }

    NOINLINE static void puthex8(uint8_t b)
    {
        puthex4(b >> 4);
        puthex4(b & 0xf);
    }

    static void puthex8(uint8_t *buf, int len)
    {
        while (len--)
            puthex8(*buf++);
    }

    NOINLINE static void puthex16(uint16_t v)
    {
        puthex8(v >> 8);
        puthex8(v  & 0xff);
    }

    NOINLINE static void putdec(uint16_t v)
    {
        char buf[6];
        char *p = buf + 5;
        *p = 0;
        do {
            *--p = (v % 10) + '0';
            v = v / 10;
        } while (v > 0);
        putstr(p);
    }

    NOINLINE static void printf(const char *format, ...)
    {
        va_list args;
        va_start(args, format);
        char c;

        while (c = *format++) {
            if (c == '%') {
                switch (c = *format++) {
                case 'x':
                    puthex16(va_arg(args, int));
                    break;
                case 'd':
                    putdec(va_arg(args, int));
                    break;
                case 's':
                    putstr(va_arg(args, const char *));
                    break;
                default:
                    goto putc;
                }
            } else {
putc:
                if (c == '\n')
                    newline();
                else
                    putc(c);
            }
        }

        va_end(args);
    }

    NOINLINE static int readline(char *buf, int size)
    {
        char *p = buf;
        while (1) {
            char c = byte_writer::read();
            if (c == '\x7f') {
                if (p > buf) {
                    p--;
                    putstr("\b \b");
                }
                continue;
            }
            if (c == '\r') {
                newline();
                *p = 0;
                break;
            }
            if (p < buf + size - 1) {
                putc(c);
                *p++ = c;
            }
        }
        // Return number of entered chars
        return p - buf;
    }
};

#endif // _CONSOLE_HPP
