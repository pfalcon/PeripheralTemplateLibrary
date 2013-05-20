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
#undef putc

namespace PTL {

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
        puthex8(v & 0xff);
    }

    static void puthex32(uint32_t v)
    {
        puthex16(v >> 16);
        puthex16(v);
    }

    NOINLINE static void putdecu16(uint16_t v)
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

    NOINLINE static void putdeci16(int16_t v)
    {
        if (v < 0) {
            putc('-');
            v = -v;
        }
        putdecu16(v);
    }

    NOINLINE static void putdecu32(uint32_t v)
    {
        char buf[sizeof("4294967295")];
        char *p = buf + sizeof(buf) - 1;
        *p = 0;
        do {
            *--p = (v % 10) + '0';
            v = v / 10;
        } while (v > 0);
        putstr(p);
    }

    NOINLINE static void putdeci32(int32_t v)
    {
        if (v < 0) {
            putc('-');
            v = -v;
        }
        putdecu32(v);
    }

    ALWAYS_INLINE static void putdec(int16_t v)
    {
        putdeci16(v);
    }

    ALWAYS_INLINE static void putdec(uint16_t v)
    {
        putdecu16(v);
    }

    ALWAYS_INLINE static void putdec(int32_t v)
    {
        putdeci32(v);
    }

    ALWAYS_INLINE static void putdec(uint32_t v)
    {
        putdecu32(v);
    }


    NOINLINE static void printf(const char *format, ...)
    {
        va_list args;
        va_start(args, format);
        char c;
#define FLAG_LONG 1
        uint8_t flags;

        while (c = *format++) {
            if (c == '%') {
                flags = 0;
format_again:
                switch (c = *format++) {
                case 'l':
                    flags |= FLAG_LONG;
                    goto format_again;
                case 'x':
                    if (flags & FLAG_LONG)
                        puthex32(va_arg(args, uint32_t));
                    else
                        puthex16(va_arg(args, int));
                    break;
                case 'd':
                    if (flags & FLAG_LONG)
                        putdeci32(va_arg(args, int32_t));
                    else
                        putdeci16(va_arg(args, int16_t));
                    break;
                case 'u':
                    if (flags & FLAG_LONG)
                        putdecu32(va_arg(args, uint32_t));
                    else
                        putdecu16(va_arg(args, uint16_t));
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

// Class name is kinda compatibility with Arduino API
class Printer
{
public:
    void write(uint8_t c);
    uint8_t read();
};

/*
 * Class to wrap object implementing Printer interface above into
 * a static type which can be passed to Console. Usage example:
 *
 * WriterClass writer; // defines write() non-static method; must be in
 *                     // global scope due to C++03 limitations
 * Console< WriterWrapper<writer> >::putstr("It works!");
 */

#if 0
// In C++, template arguments are not covariant,
// i.e. we cannot pass a subclass of Printer here,
// so have to pass complete pair of <type, object>
// instead
// See http://stackoverflow.com/questions/13606483/c-nontype-template-argument-taking-inherited-class
template <Printer& byte_writer>
#else
template <typename T, T& byte_writer>
#endif
class WriterWrapper
{
public:
    static void write(uint8_t c)
    {
        byte_writer.write(c);
    }

    static uint8_t read()
    {
        return byte_writer.read();
    }
};


} // namespace

#endif // _CONSOLE_HPP
