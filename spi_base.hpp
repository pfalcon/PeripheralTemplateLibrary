class ISPI
{
public:
    static void init();
    static uint8_t transfer(uint8_t b);
};


template <class spi_impl>
class SPIBlockXfer
{
public:
    // Oftentimes, duplex SPI transfers are not used,
    // and instead separate read/write transactions
    // are used. Functions below allow for efficient
    // implementation of such, with basic default
    // implementation provided.
    static void read_block(uint8_t *buf, uint8_t len);
    static void write_block(uint8_t *buf, uint8_t len);
};

template <class spi_impl>
void SPIBlockXfer<spi_impl>::read_block(uint8_t *buf, uint8_t len)
{
    while (len--) {
        *buf++ = spi_impl::transfer(0xFF);
    }
}

template <class spi_impl>
void SPIBlockXfer<spi_impl>::write_block(uint8_t *buf, uint8_t len)
{
    while (len--) {
         spi_impl::transfer(*buf++);
    }
}
