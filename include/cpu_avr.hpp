#include <cpu_base.hpp>
#include <avr/wdt.h>

class AVRCPU {};

template <>
class CPU<AVRCPU> : public ICPU
{
public:
    static void init(int flags)
    {
#if 0
        switch (flags) {
        case DEFAULT:
            wdt_disable();
            break;
        }
#endif
    }
};

typedef CPU<AVRCPU> cpu;
