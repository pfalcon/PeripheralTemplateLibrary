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
#include <uart.hpp>
#include <rtos/circular.hpp>

namespace PTL {

template <class uart, int read_buf_sz, int write_buf_sz, template<typename, int> class buffer = PTL::CircularBuffer>
class BufferedUart
{
    typedef BufferedUart<uart, read_buf_sz, write_buf_sz, buffer> self;
    //typename 
    buffer<uint8_t, read_buf_sz> read_buf;
    //typename 
    buffer<uint8_t, write_buf_sz> write_buf;

    template <self& me>
    class uart_handlers : public uart
    {
    public:
        static void irq_rx()
        {
            if (me.read_buf.full())
                overrun();
            else
                me.read_buf.push(uart::read_async());
        }
        static void irq_tx()
        {
            assert(!me.write_buf.empty());
            uint8_t c = me.write_buf.pop();
            uart::write_async(c);
            // If there's nothing more to send, disable TX IRQ
            // (really "TX Buffer Empty IRQ")
            if (me.write_buf.empty())
                uart::disable_tx_irq();
        }
    };

public:
    void init()
    {
        // We always should expect to receive something
        uart::enable_rx_irq();
        // but in the beginning, there's nothing to send -
        // interrupts will be enabled on first char to send
        uart::disable_tx_irq();
    }
    uint8_t read()
    {
        while (read_buf.empty());
        return read_buf.pop();
    }
    void write(uint8_t c)
    {
        while (write_buf.full());
        write_buf.push(c);
        uart::enable_tx_irq();
    }

    // Override
    void overrun()
    {
    }

};

} // namespace
