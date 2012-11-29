#include <stdint.h>

class byteptr
{
public:
    static uint16_t _uint16_t(void *p) { return (((uint8_t*)p)[1] << 8) | *(uint8_t*)p; }
    static void _uint16_t(void *p, uint16_t val) { *(uint8_t*)p = val; ((uint8_t*)p)[1] = val >> 8; }
};
