#include <board_base.hpp>
#include <gpio.hpp>

class MSP430Launchpad {};

template <>
class Board<MSP430Launchpad>
{
public:
    typedef Pin<P1, Bit0> LED;
};

typedef Board<MSP430Launchpad> board;
