#include <signal.hpp>
#include <parallel_bus.hpp>
#include <uart.hpp>
#include <spi.hpp>

using namespace PTL;

//typedef UART<board::freq, 9600, board::pin_uart_tx, board::pin_uart_rx, timer> uart;
typedef UART<1 MHZ, 9600, USCI_A> uart;

typedef SPI<USCI_B> spi;

typedef ParBus< Pin<P1, Bit5>, Pin<P1, Bit4>, Pin<P1, Bit3>, Pin<P1, Bit2> > hd44780_data;
typedef Signal< Pin<P1, Bit6> > hd44780_en_sig;
typedef Signal< Pin<P1, Bit7> > hd44780_regsel_sig;
