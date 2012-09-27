// Based on http://en.wikipedia.org/wiki/I%C2%B2C

template <class sda, class scl, class delayer, int delay_>
class I2C
{
public:
    static void init()
    {
        sda_high();
        scl_high();
    }

    static void sda_high()
    {
        sda::input();
        sda::pullup();
    }
    static void sda_low()
    {
        sda::output();
        sda::low();
    }

    static void scl_high()
    {
        scl::input();
        scl::pullup();
    }
    static void scl_low()
    {
        scl::output();
        scl::low();
    }

    static void delay()
    {
        delayer::delay(delay_);
    }



    static void start()
    {
        sda_low();
        delay();
        scl_low();
        delay();
    }

    static void restart()
    {
        sda_high();
        delay();
        scl_high();
        delay();
        start();
    }

    static void stop()
    {
        sda_low();
        scl_high();
        delay();
        sda_high();
        delay();
    }

    static typename sda::port::width read_bit()
    {
        sda_high();
        scl_high();
        delay();
        uint8_t ack = sda::value();
        scl_low();
        return ack;
    }

    static typename sda::port::width write_bit(uint8_t val)
    {
        if (val)
            sda_high();
        else
            sda_low();
        delay();
        scl_high();
        delay(); // Rather should sense scl for clock stretching
        scl_low();
    }

    static typename sda::port::width write(uint8_t b)
    {
        for (int i = 8; i--;) {
            write_bit(b & 0x80);
            b <<= 1;
        }
        return read_bit();
    }

    static uint8_t read(bool ack = true)
    {
        uint8_t b = 0;
        for (int i = 8; i--;) {
            b <<= 1;
            if (read_bit())
                b |= 1;
        }
        write_bit(!ack);
        return b;
    }
};
