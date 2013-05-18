#include <stdint.h>

namespace PTL {

class Delay
{
public:
    typedef uint32_t width;

    static void delay(width cycles)
    {
        // call to here: 1 cycle
#define ADJUST (1/*delay arg load*/ + 1/*call*/ + 1/*ret*/)
        cycles = ((cycles - ADJUST) + 2) / 3;
        asm __volatile__ (
            "1: \n"
            "subs %[value], #1 \n" //1
            "bne 1b \n" // 2
            : [value] "+r" (cycles) :
        );
    }
};

} // namespace
