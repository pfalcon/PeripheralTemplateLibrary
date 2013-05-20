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


#ifndef PCD8544_H
#define PCD8544_H


#include <compat/arduino.hpp>
#include <console.hpp>

namespace PTL {

// Chip variants supported...
#define CHIP_PCD8544 0
#define CHIP_ST7576  1

template <class delayer,
          class pin_sclk, class pin_sdin, class pin_dc, class pin_reset, class pin_sce,
          unsigned width = 84, unsigned height = 48>
class PCD8544 : public Printer {
    public:
        // Display initialization (dimensions in pixels)...
        void begin(unsigned char model=CHIP_PCD8544);
        void stop();

        // Erase everything on the display...
        void clear();
        void clearLine();  // ...or just the current line
        
        // Control the display's power state...
        static void setPower(bool on);

        // For compatibility with the LiquidCrystal library...
        static void display();
        static void noDisplay();

        // Activate white-on-black mode (whole display)...
        static void setInverse(bool inverse);

        // Place the cursor at the start of the current line...
        void home();

        // Place the cursor at position (column, line)...
        void setCursor(unsigned char column, unsigned char line);

        // Assign a user-defined glyph (5x8) to an ASCII character (0-31)...
        void createChar(unsigned char chr, const unsigned char *glyph);

        // Write an ASCII character at the current cursor position (7-bit)...
        void write(uint8_t chr);

        // Draw a bitmap at the current cursor position...
        void drawBitmap(const unsigned char *data, unsigned char columns, unsigned char lines);

        // Draw a chart element at the current cursor position...
        void drawColumn(unsigned char lines, unsigned char value);

    private:
        // Current cursor position...
        unsigned char column;
        unsigned char line;

        // User-defined glyphs (below the ASCII space character)...
        const unsigned char *custom[' '];

        // Send a command or data to the display...
        static void send(unsigned char type, unsigned char data);
};

#include <device/pcd8544.cpp>

} // namespace

#endif  /* PCD8544_H */
