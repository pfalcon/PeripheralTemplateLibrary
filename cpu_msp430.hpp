#include <cpu_base.hpp>
#include <msp430.h>

class MSP430CPU {};

template <>
class CPU<MSP430CPU> : public ICPU
{
public:
    static void init(int flags)
    {
        switch (flags) {
        case DEFAULT:
            // Disable watchdog
            WDTCTL = WDTPW | WDTHOLD;
            break;
        }
    }
};

typedef CPU<MSP430CPU> cpu;
