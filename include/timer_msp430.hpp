#include <timer_base.hpp>

template <int ctrl_reg_, int val_reg_, int intr_reg_>
class Timer : public ITimer<uint16_t>
{
public:
    static const int ctrl_reg = ctrl_reg_;
    static const int val_reg = val_reg_;
    static const int intr_reg = intr_reg_;

    static width value() { return *(volatile width*)val_reg; }
    static void free_run();

    static void delay(width cycles)
    {
        width start = value();
        delay_since(start, cycles);
    }
    static void delay_since(width since, width delay)
    {
        while (value() - since < delay);
    }

};

template <int ctrl_reg_, int val_reg_, int intr_reg_>
void Timer<ctrl_reg_, val_reg_, intr_reg_>::free_run()
{
    // SMCLK, continuous mode
    TACTL = TASSEL_2 | MC_2;
}

typedef Timer<TACTL_, TAR_, TAIV_> Timer0_A;
#ifdef TA1CTL_
typedef Timer<TACTL_, TAR_, TAIV_> Timer1_A;
#endif
typedef Timer0_A timer;
