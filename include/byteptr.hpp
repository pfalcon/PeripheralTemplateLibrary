#include <stdint.h>

class byteptr
{
public:
    static uint16_t _uint16_t(const void *p)
    {
        const uint8_t *t = (uint8_t*)p;
        return (t[1] << 8) | t[0];
    }

    static void _uint16_t(void *p, uint16_t val)
    {
        uint8_t *t = (uint8_t*)p;
        t[0] = val;
        t[1] = val >> 8;
    }

    static uint32_t _uint32_t(const void *p)
    {
        const uint8_t *t = (uint8_t*)p;
        return ((uint32_t)t[3] << 24) | ((uint32_t)t[2] << 16) | (t[1] << 8) | t[0];
    }

    static void _uint32_t(void *p, uint32_t val)
    {
        uint8_t *t = (uint8_t*)p;
        t[0] = val;
        t[1] = val >> 8;
        t[2] = val >> 16;
        t[3] = val >> 24;
    }
};
