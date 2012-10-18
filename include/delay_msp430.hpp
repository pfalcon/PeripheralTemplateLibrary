#include <stdint.h>

class Delay
{
public:
    typedef uint32_t width;

    static void delay(width cycles)
    {
        // call to here: 5 cycles
        // - 4 below because we do post-check, so with 0 we do 1 iteration
        cycles -= 5 + 3 + 5 + 3 - 4; // 3 clocks
        cycles >>= 2; // 5 instructions, 5 cycles
        asm(
            "1: \n"
            "sub    #1, %A0 \n" // 1 cycle
            "subc   #0, %B0 \n" // 1 cycle
            "jc    1b \n" // 2 cycles, msp430 has weird C flag value for substracts
            : : "r" (cycles)
        );
        // ret: 3 cycles
    }
};

template <uint32_t freq>
class DelayTime : public Delay
{
    static void delay_us(width us)
    {
        delay(freq * us / 1000000L);
    }

    static void delay_ms(width ms)
    {
        delay(freq * ms / 1000L);
    }
};
