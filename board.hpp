#include <gpio.hpp>

class MSP430Launchpad{};

template <class board>
class Board
{
};

template <>
class Board<MSP430Launchpad>
{
public:
    typedef Pin<P1, Bit0> LED;
};
