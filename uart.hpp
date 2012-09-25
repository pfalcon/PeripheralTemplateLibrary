#include <gpio.hpp>

template <class tx, class rx, class timer, int bit_time>
class UART
{
public:
    static void init()
    {
        tx::output();
        tx::high();
        rx::input();
    }
    static uint8_t read();
    static void write(uint8_t b);
};

template <class tx, class rx, class timer, int bit_time>
void UART<tx, rx, timer, bit_time>::write(uint8_t val)
{
    typename timer::width start;
    uint8_t bit_count = 8;

    // We fix initial transfer start time,
    // and reference all times against it, to
    // avoid accumulating error.
    start = timer::value();

    // Start bit
    tx::low();
    timer::delay_since(start, bit_time);

    // Data bits, LSB first
    do {
        if (val & 1)
            tx::high();
        else
            tx::low();
        start += bit_time;
        timer::delay_since(start, bit_time);
        val >>= 1;
    } while (--bit_count);

    // Stop bit
    tx::high();
    start += bit_time;
    timer::delay_since(start, bit_time);
}

template <class tx, class rx, class timer, int bit_time>
uint8_t UART<tx, rx, timer, bit_time>::read()
{
    typename timer::width start;
    uint8_t bit_count = 8;
    typename rx::port::width val;
    uint8_t b = 0;

    // Wait for start bit (low)
    while (rx::value());

    // We'll use absolute time reference, the same as for write()
    start = timer::value();
    // We'll sample bit values in the middle of period
    timer::delay_since(start, bit_time / 2);
    start += bit_time / 2;
    // We're at the middle of start bit now

    do {
        timer::delay_since(start, bit_time);
        val = rx::value();
        b >>= 1;
        if (val)
            b |= 0x80;
        start += bit_time;
    } while (--bit_count);

    return b;
}
