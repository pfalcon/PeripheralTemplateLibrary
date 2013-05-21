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

// This code is based on http://code.google.com/p/pcd8544/
// Original copyright and licensing are provided below.
// Please note that they are no longer apply to the version
// in Peripheral Template Library, which undergone changes.
// Terms below are provided only to comply with wording of the
// license (and the wording also allows to relicense derivative
// product under another license).

/*
 * PCD8544 - Interface with Philips PCD8544 (or compatible) LCDs.
 *
 * Copyright (c) 2010 Carlos Rodrigues <cefrodrigues@gmail.com>
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 * THE SOFTWARE.
 */

extern "C" {
#include <string.h>
}
#include <progmem.hpp>

#define PCD8544_CMD  LOW
#define PCD8544_DATA HIGH


/*
 * If this was a ".h", it would get added to sketches when using
 * the "Sketch -> Import Library..." menu on the Arduino IDE...
 */
#include "device/charset_6x8.cpp"


template <class delayer, class pin_sclk, class pin_sdin, class pin_dc, class pin_reset, class pin_sce,
          unsigned width, unsigned height>
void PCD8544<delayer, pin_sclk, pin_sdin, pin_dc, pin_reset, pin_sce, width, height>::begin(unsigned char model)
{
    this->column = 0;
    this->line = 0;

    // Sanitize the custom glyphs...
    memset(this->custom, 0, sizeof(this->custom));

    // All pins are outputs (these displays cannot be read)...
    pinMode(pin_sclk, OUTPUT);
    pinMode(pin_sdin, OUTPUT);
    pinMode(pin_dc, OUTPUT);
    pinMode(pin_reset, OUTPUT);
    pinMode(pin_sce, OUTPUT);

    // Reset the controller state...
    digitalWrite(pin_reset, HIGH);
    digitalWrite(pin_sce, HIGH);
    digitalWrite(pin_reset, LOW);
    delay(100);  
    digitalWrite(pin_reset, HIGH);

    // Set the LCD parameters...
    send(PCD8544_CMD, 0x21);  // extended instruction set control (H=1)
    send(PCD8544_CMD, 0x13);  // bias system (1:48)

    if (model == CHIP_ST7576) {
        send(PCD8544_CMD, 0xe0);  // higher Vop, too faint at default
        send(PCD8544_CMD, 0x05);  // partial display mode
    } else {
        send(PCD8544_CMD, 0xc2);  // default Vop (3.06 + 66 * 0.06 = 7V)
    }

    send(PCD8544_CMD, 0x20);  // extended instruction set control (H=0)
    send(PCD8544_CMD, 0x09);  // all display segments on

    // Clear RAM contents...
    this->clear();

    // Activate LCD...
    send(PCD8544_CMD, 0x08);  // display blank
    send(PCD8544_CMD, 0x0c);  // normal mode (0x0d = inverse mode)
    delay(100);

    // Place the cursor at the origin...
    send(PCD8544_CMD, 0x80);
    send(PCD8544_CMD, 0x40);
}


template <class delayer, class pin_sclk, class pin_sdin, class pin_dc, class pin_reset, class pin_sce,
          unsigned width, unsigned height>
void PCD8544<delayer, pin_sclk, pin_sdin, pin_dc, pin_reset, pin_sce, width, height>::stop()
{
    this->clear();
    setPower(false);
}


template <class delayer, class pin_sclk, class pin_sdin, class pin_dc, class pin_reset, class pin_sce,
          unsigned width, unsigned height>
void PCD8544<delayer, pin_sclk, pin_sdin, pin_dc, pin_reset, pin_sce, width, height>::clear()
{
    this->setCursor(0, 0);

    for (unsigned short i = 0; i < width * (height/8); i++) {
        send(PCD8544_DATA, 0x00);
    }

    this->setCursor(0, 0);
}


template <class delayer, class pin_sclk, class pin_sdin, class pin_dc, class pin_reset, class pin_sce,
          unsigned width, unsigned height>
void PCD8544<delayer, pin_sclk, pin_sdin, pin_dc, pin_reset, pin_sce, width, height>::clearLine()
{
    this->setCursor(0, this->line);

    for (unsigned char i = 0; i < width; i++) {
        send(PCD8544_DATA, 0x00);
    }

    this->setCursor(0, this->line);
}


template <class delayer, class pin_sclk, class pin_sdin, class pin_dc, class pin_reset, class pin_sce,
          unsigned width, unsigned height>
void PCD8544<delayer, pin_sclk, pin_sdin, pin_dc, pin_reset, pin_sce, width, height>::setPower(bool on)
{
    send(PCD8544_CMD, on ? 0x20 : 0x24);
}


template <class delayer, class pin_sclk, class pin_sdin, class pin_dc, class pin_reset, class pin_sce,
          unsigned width, unsigned height>
inline void PCD8544<delayer, pin_sclk, pin_sdin, pin_dc, pin_reset, pin_sce, width, height>::display()
{
    setPower(true);
}


template <class delayer, class pin_sclk, class pin_sdin, class pin_dc, class pin_reset, class pin_sce,
          unsigned width, unsigned height>
inline void PCD8544<delayer, pin_sclk, pin_sdin, pin_dc, pin_reset, pin_sce, width, height>::noDisplay()
{
    setPower(false);
}


template <class delayer, class pin_sclk, class pin_sdin, class pin_dc, class pin_reset, class pin_sce,
          unsigned width, unsigned height>
void PCD8544<delayer, pin_sclk, pin_sdin, pin_dc, pin_reset, pin_sce, width, height>::setInverse(bool inverse)
{
    send(PCD8544_CMD, inverse ? 0x0d : 0x0c);
}


template <class delayer, class pin_sclk, class pin_sdin, class pin_dc, class pin_reset, class pin_sce,
          unsigned width, unsigned height>
void PCD8544<delayer, pin_sclk, pin_sdin, pin_dc, pin_reset, pin_sce, width, height>::home()
{
    this->setCursor(0, this->line);
}


template <class delayer, class pin_sclk, class pin_sdin, class pin_dc, class pin_reset, class pin_sce,
          unsigned width, unsigned height>
void PCD8544<delayer, pin_sclk, pin_sdin, pin_dc, pin_reset, pin_sce, width, height>::setCursor(unsigned char column, unsigned char line)
{
    this->column = (column % width);
    this->line = (line % (height/9 + 1));

    send(PCD8544_CMD, 0x80 | this->column);
    send(PCD8544_CMD, 0x40 | this->line); 
}


template <class delayer, class pin_sclk, class pin_sdin, class pin_dc, class pin_reset, class pin_sce,
          unsigned width, unsigned height>
void PCD8544<delayer, pin_sclk, pin_sdin, pin_dc, pin_reset, pin_sce, width, height>::createChar(unsigned char chr, const unsigned char *glyph)
{
    // ASCII 0-31 only...
    if (chr >= ' ') {
        return;
    }
    
    this->custom[chr] = glyph;
}


template <class delayer, class pin_sclk, class pin_sdin, class pin_dc, class pin_reset, class pin_sce,
          unsigned width, unsigned height>
void PCD8544<delayer, pin_sclk, pin_sdin, pin_dc, pin_reset, pin_sce, width, height>::write(uint8_t chr)
{
    // ASCII 7-bit only...
    if (chr >= 0x80) {
        return;
    }

    const unsigned char *glyph;
    unsigned char pgm_buffer[5];

    if (chr >= ' ') {
        // Regular ASCII characters are kept in flash to save RAM...
        memcpy_progmem(pgm_buffer, &charset[chr - ' '], sizeof(pgm_buffer));
        glyph = pgm_buffer;
    } else {
        // Custom glyphs, on the other hand, are stored in RAM...
        if (this->custom[chr]) {
            glyph = this->custom[chr];
        } else {
            // Default to a space character if unset...
            memcpy_progmem(pgm_buffer, &charset[0], sizeof(pgm_buffer));
            glyph = pgm_buffer;
        }
    }

    // Output one column at a time...
    for (unsigned char i = 0; i < 5; i++) {
        send(PCD8544_DATA, glyph[i]);
    }

    // One column between characters...
    send(PCD8544_DATA, 0x00);

    // Update the cursor position...
    this->column = (this->column + 6) % width;

    if (this->column == 0) {
        this->line = (this->line + 1) % (height/9 + 1);
    }
}


template <class delayer, class pin_sclk, class pin_sdin, class pin_dc, class pin_reset, class pin_sce,
          unsigned width, unsigned height>
void PCD8544<delayer, pin_sclk, pin_sdin, pin_dc, pin_reset, pin_sce, width, height>::drawBitmap(const unsigned char *data, unsigned char columns, unsigned char lines)
{
    unsigned char scolumn = this->column;
    unsigned char sline = this->line;

    // The bitmap will be clipped at the right/bottom edge of the display...
    unsigned char mx = (scolumn + columns > width) ? (width - scolumn) : columns;
    unsigned char my = (sline + lines > height/8) ? (height/8 - sline) : lines;

    for (unsigned char y = 0; y < my; y++) {
        this->setCursor(scolumn, sline + y);

        for (unsigned char x = 0; x < mx; x++) {
            send(PCD8544_DATA, data[y * columns + x]);
        }
    }

    // Leave the cursor in a consistent position...
    this->setCursor(scolumn + columns, sline);
}


template <class delayer, class pin_sclk, class pin_sdin, class pin_dc, class pin_reset, class pin_sce,
          unsigned width, unsigned height>
void PCD8544<delayer, pin_sclk, pin_sdin, pin_dc, pin_reset, pin_sce, width, height>::drawColumn(unsigned char lines, unsigned char value)
{
    unsigned char scolumn = this->column;
    unsigned char sline = this->line;

    // Keep "value" within range...
    if (value > lines*8) {
        value = lines*8;
    }

    // Find the line where "value" resides...
    unsigned char mark = (lines*8 - 1 - value)/8;
    
    // Clear the lines above the mark...
    for (unsigned char line = 0; line < mark; line++) {
        this->setCursor(scolumn, sline + line);
        send(PCD8544_DATA, 0x00);
    }

    // Compute the byte to draw at the "mark" line...
    unsigned char b = 0xff;
    for (unsigned char i = 0; i < lines*8 - mark*8 - value; i++) {
        b <<= 1;
    }

    this->setCursor(scolumn, sline + mark);
    send(PCD8544_DATA, b);

    // Fill the lines below the mark...
    for (unsigned char line = mark + 1; line < lines; line++) {
        this->setCursor(scolumn, sline + line);
        send(PCD8544_DATA, 0xff);
    }
  
    // Leave the cursor in a consistent position...
    this->setCursor(scolumn + 1, sline); 
}


template <class delayer, class pin_sclk, class pin_sdin, class pin_dc, class pin_reset, class pin_sce,
          unsigned width, unsigned height>
void PCD8544<delayer, pin_sclk, pin_sdin, pin_dc, pin_reset, pin_sce, width, height>::send(unsigned char type, unsigned char data)
{
    digitalWrite(pin_dc, type);
  
    digitalWrite(pin_sce, LOW);
    shiftOut(pin_sdin, pin_sclk, MSBFIRST, data);
    digitalWrite(pin_sce, HIGH);
}
