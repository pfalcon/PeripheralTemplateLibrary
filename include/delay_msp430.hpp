template <long cycles, bool toobig = (cycles > 32767)>
class MSP430Delay
{
public:
    static void delay()
    {
        __delay_cycles(cycles);
    }
};

template <long cycles>
class MSP430Delay<cycles, true>
{
public:
    static void delay()
    {
        for (int i = cycles / 32765; i; i--)
            __delay_cycles(32765);
        __delay_cycles(cycles % 32765);
    }
};

template <long cycles>
inline void delay()
{
    MSP430Delay<cycles>::delay();
}
