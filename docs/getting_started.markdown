Getting Started with Peripheral Template Library
================================================

This documents provides instructions on development environment setup to
compile a simple PTL example application. These instructions assume that
Ubuntu Linux OS is used, and were verified on 12.04 LTS (Long-Term Support)
release. If you use much older Ubuntu version, different Linux distribution,
or completely different OS like MacOS or Windows, one easy way to still
get started quickly is to use Ubuntu 12.04 in a Virtual Machine (VM), like
VirtualBox. This way is becoming more and more mainstream nowadays, and is
highly recommended, as it will allow you to avoid additional setup and
maintenance efforts.

Of course, using VM is not a requirement, and PTL is written in portable
manner, depending only on basic GNU/POSIX system features, which are
available on any modern OS. A sufficiently advanced user will be able to
easily set up development environment on any of the systems listed above,
for example:

* Many of popular Linux distros should provide MCU toolchain packages
  similar to Ubuntu, maybe just having slightly different names. If your
  distro doesn't provide them, or versions are too old (generally, try to
  avoid gcc below 4.5), you can compile them from source.
* For MacOS, similar "ports" facilities exist, using which you can install
  toochains without much of manual work
* For Windows, you can use Cygwin for GNU/POSIX environment and easily
  find precompiled toolchains and support utilities.

Once again, you will just need to have some developmeny experience with your
target system if you go this way. Internet search will usually resolve any
hiccups you may have.

Installing development packages
-------------------------------
This section gives commands to install packages for particular MCU target
architecture. You don't have to install them all - you can start with
just one architecture and install more when you actually need them.


### Installing basic development environment

This installs generic development packages, like GNU make or host compiler,
you need to do this once before installing target-specific toolchain.

    sudo apt-get install make gcc g++

### Installing MSP430 toolchain

You will need this to develop for Texas Instruments MSP430 Launchpad board
for example.

    sudo apt-get install binutils-msp430 gcc-msp430 \
        msp430-libc msp430mcu mspdebug

### Installing AVR toolchain

You will need this to develop for "classic" AVR Arduino boards (Duemilanove,
Leonardo, etc.)

    sudo apt-get install binutils-avr gcc-avr \
        avr-libc avrdude

