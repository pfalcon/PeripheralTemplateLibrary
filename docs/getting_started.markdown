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

### Installing ARM Cortex-M toolchain and libs

Most of Linux distros nowadays come with ARM toolchain, but that usually
targets Cortex-A CPUs. What differs Cortex-A and Cortex-M support (we need
the latter) is usually just system libs, including compiler support libs.
It might be possible to use Cortex-A toolchain, but that would lead to
warnings, and needs to be tested well first to make sure that bigger issues
don't creep in.

So, instead the toolchain which specifically targets Cortex-M is recommended:
https://launchpad.net/gcc-arm-embedded . This project provides prebuilt
binaries for Linux, Windows, and MacOS. For Ubuntu LTS releases, PPA (package
repository) is provided (recommended).

[TODO: give specific commands to install.]

Installing PTL and support libraries
------------------------------------
Decide where you will check out PTL and support libraries. We'll call
that directory $PARENT in the text below. To checkout PTL, change to
$PARENT and run:

    git clone https://github.com/pfalcon/PeripheralTemplateLibrary.git

For Cortex-M support, you will also need CMSIS libraries and startup files
for specific MCUs. CMSIS implementation for Cortex-M core was recently
open-sourced by ARM, but support for specific MCU's peripherals depends
on vendors, and vendor CMSIS implementations usually come with proprietary
license, which may contaminate licensing of entire OpenSource projects
built using PTL. To resolve this issue, PTL uses completely open-source,
CMSIS-compatible layer called "libperipha". Libperipha is brough to you
by the same developers as PTL, and was split out of PTL for easier reuse
(for example, libperipha doesn't rely on C++ and can be used in C projects).
Last piece of puzzle is generic Cortex-M startup file library, called
cortex-uni-startup.

All of PTL, libperipha, and cortex-uni-startup are by default expected to
reside on the same directory level, i.e. in $PARENT dir. So to get
Cortex-M support libs, change directory to $PARENT and run following commands:

    git clone --recursive https://github.com/pfalcon/libperipha.git
    git clone https://github.com/pfalcon/cortex-uni-startup.git

Building first PTL example application
--------------------------------------
Once you've done steps above, you should be ready to compile PTL applications.
Classical hello-world style example application for MCUs is LED blinker,
and that's how we'll start.

Assuming you are in $PARENT dir, change to PTL dir:

    cd PeripheralTemplateLibrary

This is the top-level PTL directory, where mostly Makefiles and standard files
like README is located. All other files are split per subdirectories, for
example docs/ has this Getting Started instructions and other documentation,
include/ is PTL source code (as PTL is template library, all its code is
contained in headers), and examples/ . We're interested in the latter now:

    cd examples

Let's build "blink" example now:

    make TARGET=<target> blink

Where <target> is target architecture of your board, currently supported values
are:

* msp430
* avr
* stm32
* efm32
* tm4

For each of these architectures, there is "default development board", and make
will actually builds an app for that board. See README for list of which boards
supported. For example, to build blink example for Arduino, run:

    make TARGET=avr blink

Once the application is built, you can deploy (aka upload, aka flash) it to the
board using following make command:

    make TARGET=<target> deploy-<app>

For our Arduino blink example, the exact command is:

    make TARGET=avr deploy-blink

In few seconds, you should see your board chearfully blink its LED with
frequency 1Hz.

Where to go next
----------------
examples/ directory contains number of sample applications, each usually small
and easy to follow, introducing one PTL concept or feature.

When you read previous section on building application for particular
target, you might wonder if PTL supports different boards of the same MCU
architecture. Of course it does! That "default board for an architecture" is
just a convention to keep things simple for people who just with the library.
PTL offers flexible way to support any number of boards, including custom,
purposedly built for your projects (actually, streamlined and efficient
support for that was one of the reason to create PTL). To learn about it,
follow commented code in examples/hw_config_tutorial/ .

Finally, docs/ directory contains other documentation on various topics.
It is sketchy at this time, and there is no complete reference of all
classes and functions PTL provides. That's definitely the areas where
PTL can, and should, improve. In the meantime, you just can follow
thru focused examples (in the examples/ dir) to headers referenced, most
concepts that PTL deals are simple enough and have simple API.
