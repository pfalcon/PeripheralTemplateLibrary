template <long cycles>
inline void delay()
{
    for (volatile int i = cycles / 12; i; i--) {
    }
}
