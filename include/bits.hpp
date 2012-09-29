#ifndef _BITS_HPP
#define _BITS_HPP

template <int bit>
class Bit
{
public:
    static const int value = 1 << bit;
    static const int shift = bit;
};

typedef Bit<0> Bit0;
typedef Bit<1> Bit1;
typedef Bit<2> Bit2;
typedef Bit<3> Bit3;
typedef Bit<4> Bit4;
typedef Bit<5> Bit5;
typedef Bit<6> Bit6;
typedef Bit<7> Bit7;
typedef Bit<8> Bit8;
typedef Bit<9> Bit9;
typedef Bit<10> Bit10;
typedef Bit<11> Bit11;
typedef Bit<12> Bit12;
typedef Bit<13> Bit13;
typedef Bit<14> Bit14;
typedef Bit<15> Bit15;

#endif //_BITS_HPP
