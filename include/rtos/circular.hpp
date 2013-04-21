template <int max_size_>
class CircularBuffer
{
    uint8_t buf[max_size_];
    uint8_t *head, *tail;
    uint8_t _size;
public:
    CircularBuffer() : head(buf), tail(buf), _size(0) {}

    int size()
    {
        return _size;
    }

    int free_size()
    {
        return max_size_ - _size;
    }

    bool is_empty()
    {
        return _size == 0;
    }

    bool is_full()
    {
        return _size == max_size_;
    }

    void push(uint8_t b)
    {
        *tail++ = b;
        if (tail >= buf + max_size_)
            tail = buf;
        _size++;
    }

    void push(const uint8_t *p, uint8_t len)
    {
        while (len--) {
            push(*p++);
        }
    }

    bool push_checked(uint8_t b)
    {
        if (is_full())
            return false;
        push(b);
        return true;
    }

    uint8_t pop()
    {
        uint8_t b = *head++;
        if (head >= buf + max_size_)
            head = buf;
        _size--;
        return b;
    }

    uint8_t pop_checked()
    {
        if (is_empty())
            return 0;
        return pop();
    }
};
