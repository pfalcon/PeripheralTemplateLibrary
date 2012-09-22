#ifndef _GPIO_AVR_HPP
#define _GPIO_AVR_HPP

#include <gpio_base.hpp>
// Make register defines be just integer addresses
#define _SFR_ASM_COMPAT 1
#include <avr/io.h>


template <int in_reg_, int out_reg_, int dir_reg_>
class Port : public IPort
{
public:
    static const int in_reg = in_reg_;
    static const int out_reg = out_reg_;
    static const int dir_reg = dir_reg_;
};

#ifdef PINA
typedef Port<PINA, PORTA, DDRA> PA;
#endif
#ifdef PINB
typedef Port<PINB, PORTB, DDRB> PB;
#endif
#ifdef PINC
typedef Port<PINC, PORTC, DDRC> PC;
#endif
#ifdef PIND
typedef Port<PIND, PORTD, DDRD> PD;
#endif

template <class port_, class bit>
class Pin : IPin
{
public:
    typedef port_ port;

    static uint8_t value()
    {
        return *(volatile uint8_t*)port::in_reg & bit::value;
    }
    static void high()
    {
        *(volatile uint8_t*)port::out_reg |= bit::value;
    }
    static void low()
    {
        *(volatile uint8_t*)port::out_reg &= ~bit::value;
    }
    static void output()
    {
        *(volatile uint8_t*)port::dir_reg |= bit::value;
    }
    static void input()
    {
        *(volatile uint8_t*)port::dir_reg &= ~bit::value;
    }
};

#endif //_GPIO_AVR_HPP
