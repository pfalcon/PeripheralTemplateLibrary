#include <board_base.hpp>
#include <gpio.hpp>

class Arduino {};

template <>
class Board<Arduino>
{
public:
    // "digital pin 13"
    typedef Pin<PB, Bit5> LED;
};

typedef Board<Arduino> board;
