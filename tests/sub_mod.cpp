#include <cassert>
#include <timer_base.hpp>

using namespace PTL;

class Dummy {};

uint32_t v0x10 = 0x10;
uint32_t v0x20 = 0x20;
uint32_t v0xffffff = 0xffffff;

int main()
{
    typedef ITimer<Dummy, COUNT_DOWN, uint32_t, 24> test_timer;
    assert((test_timer::sub_mod(0x20, 0x10) == 0x10));
    assert((test_timer::sub_mod(0x10, 0xffffff) == 0x11));
    assert((test_timer::sub_mod(0x10, 0x20) == 0xfffff0));

    assert((test_timer::sub_mod(v0x20, v0x10) == 0x10));
    assert((test_timer::sub_mod(v0x10, v0xffffff) == 0x11));
    assert((test_timer::sub_mod(v0x10, v0x20) == 0xfffff0));
}
