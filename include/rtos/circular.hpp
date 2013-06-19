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
namespace PTL {

template <typename elem, int max_size_>
class CircularBuffer
{
    elem buf[max_size_];
    elem *head, *tail;
    uint8_t _size;
public:
    CircularBuffer() : head(buf), tail(buf), _size(0) {}

    /* std:queue compliant methods */

    int size() const
    {
        return _size;
    }

    bool empty() const
    {
        return _size == 0;
    }

    void push(elem e)
    {
        *tail++ = e;
        if (tail >= buf + max_size_)
            tail = buf;
        _size++;
    }

    elem pop()
    {
        elem e = *head++;
        if (head >= buf + max_size_)
            head = buf;
        _size--;
        return e;
    }

    elem front() const
    {
        return *head;
    }

    // No back, sorry
    //elem back() const;

    /* extended methods */

    int free_size() const
    {
        return max_size_ - _size;
    }

    bool full() const
    {
        return _size == max_size_;
    }

    bool has_free_size(unsigned size)
    {
        return free_size() >= size;
    }

    void push(const elem *p, uint8_t len)
    {
        while (len--) {
            push(*p++);
        }
    }

    bool push_checked(elem b)
    {
        if (full())
            return false;
        push(b);
        return true;
    }

    elem pop_checked()
    {
        if (empty())
            return 0;
        return pop();
    }

    /* Read/write interface */
    void write(elem b) { push_checked(b); }
    // Checking that buffer contains enough elements is on the caller
    elem read() { return pop(); }
};

} // namespace
