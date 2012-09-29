template <long cycles>
inline void delay()
{
    __builtin_avr_delay_cycles(cycles);
}
