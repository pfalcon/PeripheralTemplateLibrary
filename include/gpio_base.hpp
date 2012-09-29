#ifndef _GPIO_BASE_HPP
#define _GPIO_BASE_HPP

#include <stdio.h>
#include <stdint.h>
#include <bits.hpp>

class IPort
{
public:
    // Enable port for access (power on, set up clocks, etc.)
    static void enable() {}
    // Disable port (power off)
    static void disable() {}
};

class IPin
{
    static void output();
    static void input();
    // TODO: need better type
    static int  value();
    static void high();
    static void low();
    static void pulloff();
    static void pullup();
    static void pulldown();
};

#endif //_GPIO_BASE_HPP
