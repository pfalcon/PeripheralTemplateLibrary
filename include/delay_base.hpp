template <long cycles>
inline void delay();

template <long freq, long us>
inline void delay_us()
{
    delay<freq * us / 1000000L>();
}

template <long freq, long ms>
inline void delay_ms()
{
    delay<(freq / 1000L) * ms>();
}
