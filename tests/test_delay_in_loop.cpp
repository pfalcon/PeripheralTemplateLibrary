#include <delay_static.hpp>

using namespace PTL;

extern "C" {

void test_delay_in_loop()
{
    while (1) {
        StaticDelay::delay(1000000U);
    }
}

}
