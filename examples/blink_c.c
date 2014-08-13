#include "blink_c_api.h"

int main()
{
    init();
    while (1) {
        led_high();
        delay(100000U);
        led_low();
        delay(100000U);
    }
}
