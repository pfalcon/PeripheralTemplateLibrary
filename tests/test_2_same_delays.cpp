#include <delay_static.hpp>

extern "C" {

void test_2_same_delays()
{
    StaticDelay::delay(1000000U);
    StaticDelay::delay(1000000U);
}

}
