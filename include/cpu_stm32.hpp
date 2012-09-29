#include <cpu_base.hpp>

class STM32CPU {};

template <>
class CPU<STM32CPU> : public ICPU
{
public:
    static void init(int flags)
    {
    }
};

typedef CPU<STM32CPU> cpu;
