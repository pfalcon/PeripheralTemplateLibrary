class ICPU
{
public:
    static const int DEFAULT = 0;
};

template <class cpu>
class CPU : public ICPU
{
};
