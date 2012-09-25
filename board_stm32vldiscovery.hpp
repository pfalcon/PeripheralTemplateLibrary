#include <board_base.hpp>
#include <gpio.hpp>

class STM32VLDiscovery {};

template <>
class Board<STM32VLDiscovery>
{
public:
    typedef Pin<PC, Bit8> LED;
    typedef Pin<PC, Bit9> LED2;
    static const long freq = 8 MHZ;
};

typedef Board<STM32VLDiscovery> board;
