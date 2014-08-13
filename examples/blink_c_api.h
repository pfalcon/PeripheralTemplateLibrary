#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

void init();
void led_high();
void led_low();
void delay(uint32_t val);

#ifdef __cplusplus
}
#endif
