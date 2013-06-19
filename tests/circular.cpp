#include <stdint.h>
#include <rtos/circular.hpp>
#if 1
#include <cassert>
#else
void assert(int) {}
#endif

using namespace PTL;

#define SIZE 10

CircularBuffer<uint8_t, SIZE> buf;

int main()
{
    assert(buf.empty());
    assert(buf.size() == 0);
    assert(buf.free_size() == SIZE);
    buf.push('a');
    assert(!buf.empty());
    assert(buf.size() == 1);
    buf.push((uint8_t*)"abcd", 4);
    assert(buf.size() == 5);
    assert(buf.pop() == 'a');
    assert(buf.pop() == 'a');
    assert(buf.pop() == 'b');
    assert(buf.pop() == 'c');
    assert(buf.pop() == 'd');

    return 0;
}
