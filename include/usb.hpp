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
#include <gpio.hpp>
#include <signal.hpp>
#include <spi.hpp>

namespace PTL {

template <>
class USB
{
    PID _next_data = PID_DATA0;
public:
    static void xact_in();
    static void xact_out(usb_addr_t addr, usb_endp_t endpoint, uint8_t *data, uint16_t len)
    {
        send_token(PID_OUT, addr, endpoint);
        send_data(next_data(), data, len);
        recv_handshake();
    }
    static void xact_setup();

    PID next_data()
    {
        PID r = _next_data;
        if (_next_data == PID_DATA0)
            _next_data == PID_DATA1;
        else
            _next_data == PID_DATA0;
    }
};

} // namespace
