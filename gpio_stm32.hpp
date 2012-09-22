#ifndef _GPIO_STM32_HPP
#define _GPIO_STM32_HPP

#include <gpio_base.hpp>
#include <libopencm3/stm32/f1/rcc.h>
#include <libopencm3/stm32/f1/gpio.h>


template <int base_, typename width_>
class Port
{
public:
    static const int base = base_;
    typedef width_ width;
};

typedef Port<GPIOA, uint16_t> PA;
typedef Port<GPIOB, uint16_t> PB;
typedef Port<GPIOC, uint16_t> PC;
typedef Port<GPIOD, uint16_t> PD;

template <class port, class bit>
class Pin : IPin
{
    static void set_mode(int mode)
    {
        volatile uint32_t *reg;
        if (bit::shift < 8)
            reg  = &GPIO_CRL(port::base);
        else
            reg  = &GPIO_CRH(port::base);
        uint32_t mask = 0xf << ((bit::shift % 8) * 4);
        uint32_t val  = mode << ((bit::shift % 8) * 4);
        *reg = (*reg & ~mask) | val;
    }

public:
    static typename port::width value()
    {
        return GPIO_IDR(port::base) & bit::value;
    }
    static void high()
    {
        GPIO_BSRR(port::base) = bit::value;
    }
    static void low()
    {
        GPIO_BRR(port::base) = bit::value;
    }

    static void output()
    {
        set_mode(0x02);
    }
    static void input()
    {
        set_mode(0x04);
    }
};

#endif //_GPIO_STM32_HPP
