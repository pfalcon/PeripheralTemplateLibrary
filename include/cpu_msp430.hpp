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
            // Use precalibrated 1MHz frequency
            BCSCTL1 = CALBC1_1MHZ;
            DCOCTL = CALDCO_1MHZ;
            break;
        }
    }
};

typedef CPU<MSP430CPU> cpu;
