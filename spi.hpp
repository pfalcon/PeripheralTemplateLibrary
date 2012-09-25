#include <gpio.hpp>

template <class sclk, class miso, class mosi>
class SPI
{
public:
    static void init()
    {
        sclk::output();
        mosi::output();
        miso::input();
    }
    static uint8_t transfer(uint8_t b);

};

template <class sclk, class miso, class mosi>
uint8_t SPI<sclk, miso, mosi>::transfer(uint8_t b)
{
        for (uint8_t i = 8; i; i--) {
            if (b & 0x80)
                mosi::high();
            else
                mosi::low();

            sclk::high();

            b <<= 1;

            if (miso::value())
                b |= 1;

            sclk::low();
        }
        return b;
}
