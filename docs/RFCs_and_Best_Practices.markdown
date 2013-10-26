RFCs and Best Practices
=======================

This document discusses various topics and usage patterns of PTL. As
PTL is work in progress, different sections have different status:
some of them describe fully implemented, proven, and recommended
solutions (Best Practices), some just provide some thoughts or
speculations on some topic, waiting for more elaboration, feedback,
and actual implementation.

Pin Function Multiplexing aka Pin Alternative Functions aka Pinmux aka Altfunc
-----------------------------------------------------------------------------
Currently, PTL lacks abstraction for setting a particular pin to one
of the functions as available in specific hardware. It would be nice
to provide some abstraction, but the main point about altfunc settings
is that they should never be done in "application" code. Instead,
specific implementation of an abtract MCU block should set needed altfunc
for pins in its init() method. So, altfunc handling is private interface
of a particular hardware implementation. Again, it would be nice to
make it consistent across implementations, but that's lower priority
than some other tasks.

If you would like to see examples how PTL handles this so far, look
at `include/msp430/spi_msp430.hpp` and `include/tm4/uart_tm4.hpp`.


RFC: Time Multiplexing of Pin Functions/Setup
---------------------------------------------

Sometimes, it is required to use different functions on the same pins at
different times. A perhaps stretched example is that on SPI pins you
have a LED and a button. Most of the time the pins handle LED and button,
but sometimes you switch them to SPI mode to do transfers to another device,
with the idea that a transfer is very short, so user won't see LED blinking,
and you just hope a user won't press a buttom during the transfer (yes, that's
why example is stretched). Another, more realistic example is that two
or more devices share same SPI bus (but different chip selects obviously),
but they need different speed settings.

As PTL aim is efficiency, it doesn't support limited-scope solutions to
do that "automatically". PTL just doesn't know when specific settings
should be used and for what duration. For example, if it allowed kind
of "event handlers" for SPI byte transfer, to allow to set up particular
settings before transfer, and then undo them after, then there would be
lot of unneeded flip-flopping for a block transfer. Apply them on block
transfer level? Then byte transfers won't be covered. Let them apply
to both (it already gets messy), then what if you need few transfers
in row? So, again, PTL can't know access patterns for pins/blocks, only
you may know. So, PTL avoids "Inversion of Control" pattern in this case,
and the way to handle this is to seprate such transfers into complete
high-level transactions, and apply needed settings explicitly to such
high-level transactions. Of course, they rather be represented as classes
for encapsulation and reuse:


Case 1:

~~~~
template <class spi>
class DeviceProtocol {
public:
    static void transact_foo() {
        spi::setup_pins();
        spi::read();
        spi::write_block();
        spi::read_block();
        ...
        spi::release_pins();
    }
};
~~~~

Case 2:
~~~~
template <class spi, class device1cs>
class Device1Protocol {
public:
    static void transact_foo() {
        spi::speed(100 KHz);
        device1cs::assert();
        spi::read();
        ...
        device1cs::deassert();
    }
};

template <class spi, class device2cs>
class Device2Protocol {
public:
    static void transact_bar() {
        spi::speed(8 MHz);
        device2cs::assert();
        spi::read();
        ...
        device2cs::deassert();
    }
};
~~~~

Note: spi setup_pins()/release_pins()/speed() methods are given as example
and may need to be added on actual demand for the scenarios described.
