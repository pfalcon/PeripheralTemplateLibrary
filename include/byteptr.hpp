#include <stdint.h>

class byteptr
{
public:
    static uint16_t _uint16_t(void *p) { return (((uint8_t*)p)[1] << 8) | *(uint8_t*)p; }
};
