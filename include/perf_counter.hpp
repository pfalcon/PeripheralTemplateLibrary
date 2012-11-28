template <class timer>
class PerfCounter
{
    typename timer::width counter;
public:
    void start() { counter = timer::value(); }
    typename timer::width stop()  { return counter = timer::value() - counter - 3 /*MSP430*/; }
    typename timer::width value()  { return counter; }
};
