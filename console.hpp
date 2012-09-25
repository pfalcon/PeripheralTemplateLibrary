template <class byte_writer>
class Console
{
public:
    void print_byte(uint8_t)
    {
    }

    static void newline()
    {
        byte_writer::write('\r');
        byte_writer::write('\n');
    }

    static void puthex4(uint8_t b)
    {
        b += '0';
        if (b > '9')
            b += 7;
        byte_writer::write(b);
    }

    static void puthex8(uint8_t b)
    {
        puthex4(b >> 4);
        puthex4(b & 0xf);
    }

    static void puthex16(uint16_t v)
    {
        puthex8(v >> 8);
        puthex8(v  & 0xff);
    }
};
