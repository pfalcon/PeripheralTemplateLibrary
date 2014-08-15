Normal C++ objects keep their state in memory fields. However, for embedded
devices, state is usually held is special registers outside usual memory
range. And even an empty (with 0 fields) C++ object takes at least 1 byte
of a memory (as mandated by C++ standard). As PTL strives for the highest
possible efficiency, wasting a whole byte for nothing is not acceptable and
C++ objects are not used for basic hardware data model. (Note, C++ objects
are used for higher-level ("RTOS-like") functionality, as there's clear
need to keep additional state in memory).

Instead, PTL uses C++ parametrized types (aka templates) to represent
hardware objects. There's rough correspondence between conventional runtime
C++ object model and typed-based schedule:

Generic entity abstraction ("class"):

Runtime OO:

    class Foo {
        Foo(type1 param1, type2 param2);
        ...
    };

Type-based OO:

    template <type1 param1, type2 param2>
    class Foo {...};

Object instantiation:

Runtime OO:

    Foo foo1(param1, param2);

Type-based OO:

    typdef Foo<param1, param2> foo1;

Passing object as argument (to function or constructor of another object):

Runtime OO:

    Bar bar1(foo1);

Type-based OO:

    typedef Bar<foo1> bar1;

Dynamic allocation:

Runtime OO:

    Foo *foo2 = new Foo(param1, param2);

Type-based OO:

    In type-based schedule, objects take 0 bytes of conventional memory,
    and keep state in implicit special memory location, so it doesn't make
    sense to "dynamically allocate" them.



Well, the last subsection about dynamic allocation is "almost true". Let's
first consider that besides efficiency PTL also strives to provide fully
generic and generalized abstraction of hardware devices, support arbitrary
possible implementations for them, and allow different abtract blocks to
be combined in structured manner. This poses interesting problem that
while typically hardware classes don't have own state (because they wrap
special hardware registers, and address them implicitly), for some
implementations of these classes there may be need to store additional
state.

Let's take a GPIO pin as an example. Typically, a pin will be represented
by:

typedef GPIO<PORT_A, PIN_0> mypin1;

Where PORT_A and PIN_0 are constants statically selecting particular port
and pin in it.

But sometimes there may be need to have "dynamic" GPIO pin, which is not
bound to a particular physical pin, but rather configured with at runtime
to use arbitrary pin. This would be obvious usecase for conventional C++
object:

GPIO mypin2(port_var, pin_var);

But we already selected type-based object representation, so mypin as defined
above won't be compatible with PTL standard model, in other word, you won't be
able to "pass" mypin2 where mypin1 is expected (per above comparison table,
type-based objects are passed as template arguments, where normal objects are
passed as normal arguments).

So, we must retain type-based interface, and yet add runtime-modifiable state
to such type. There're 2 ways to resolve this situation:

1. Split state from type-based object into "backing store":

struct GPIOStore {
    int port;
    int pin;
};

And then parametrize type-based object with reference to particular instance
of backing store:

template <GPIOStore &store>
class DynaGPIO {
};

2. Well, just store state in static fields, but making sure we parametrize
type-based object by unique values, so template instantiation leads to
distinct types (and thus distinct static variables for each type object).
For such unique values, initial/default values make work (they certainly
work for GPIO case - hopefully one won't create 2 distinct pin objects
which are actually the same pin).

template <int port_, int pin_>
class DynaGPIO {
    static int port;
    static int pin;
};

template <int port_, int pin_> int Pin<port_, pin_>::port = port_;
template <int port_, int pin_> int Pin<port_, pin_>::pin = pin_;

Note the explicit instantiation of templated static fields.


Second choice looks more "integral", because it doesn't require creation of
separate type, but it has mild tricks of requiring unique parametrization
and explicit template instantiation for static fields. And well, it's clear
that here state will be statically allocated.

First choice looks more flexible, because it would be seem that backing
store might be allocated on stack. But that's not really case, because
template parameter must be (at least in C++03) compile time addressable,
like static varaible and unlike automatic or dynamic variable.

So, choice 2 looks like clear winner as offering cleaner and more concise
interface. Choice 1 was initially implemented for DynaPin class, and
retained there for time being (to explore and see if more differences
between choices will be found), but choice 2 will be used for new classes.


