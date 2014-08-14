#include <signal.hpp>
#include <parallel_bus.hpp>
#include <uart.hpp>
#include <spi.hpp>

using namespace PTL;

//#define LAUNCHPAD_MSP430_VER_1_4

#ifndef LAUNCHPAD_MSP430_VER_1_4

/* MSP430 Launchpad hw. rev. 1.5 has different (swapped) pin assignments for
   "software" and "hardware" UART. This is rooted in the fact that hwrev. 1.4
   had "software" assignment, but later released chips with hardware UART
   had them swapped. TI decided to keep compatibility with "software" UART
   of 1.4, by providing jumpers allowing to swap pins. Obviously, that means
   that you need to switch jumpers each time to go from hardware to software
   UART and back, which is quite inconvinient. So, PTL abandons TI's "software"
   UART assignment, and instead uses just same pins as hardware UART.
   Bottom line: put jumpers in hardware UART position (perpindicular to other
   jumpers) and forget about it (while you're working with PTL). See below for
   1.4 support.
   More info: http://pfalcon-oe.blogspot.com/2012/07/ti-launchpad-14-vs-15-pin-swappery.html
   */
typedef UART<1 MHZ, 9600, USCI_A> hwuart;
//typedef UART<board::freq, 9600, board::pin_uart_tx, board::pin_uart_rx, timer> uart;
typedef UART<1 MHZ, 9600, USCI_A> uart;

/* At this time, only USCI-based hardware SPI is supported, USI still needs
   wrapping. Note that USCI vs USI SPI pins have the same swapping issue as UART
   above (great work, TI!) */
typedef SPI<USCI_B> spi;

#else

/* MSP430 Launchpad hw. rev. 1.4 doesn't have hardware UART support at all,
   and bitbang UART has to use swapped RXD/TXD pins. */
typedef UART<board::freq, 9600, Pin<P1, Bit1>, Pin<P1, Bit2>, timer> uart;

#endif

typedef ParBus< Pin<P1, Bit5>, Pin<P1, Bit4>, Pin<P1, Bit3>, Pin<P1, Bit2> > hd44780_data;
typedef Signal< Pin<P1, Bit6> > hd44780_en_sig;
typedef Signal< Pin<P1, Bit7> > hd44780_regsel_sig;

typedef Pin<P1, Bit3> pcd8544_sclk;
typedef Pin<P1, Bit4> pcd8544_sdin;
typedef Pin<P1, Bit5> pcd8544_dc;
typedef Pin<P1, Bit6> pcd8544_reset;
typedef Pin<P1, Bit7> pcd8544_sce;
