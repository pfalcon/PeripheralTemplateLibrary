template <long cycles>
inline void delay()
{
    for (volatile int i = cycles; i; i--) {
    }
}
