#include <delay_static.hpp>

extern "C" {

void test_single_delay()
{
    StaticDelay::delay(1000000U);
}

}
