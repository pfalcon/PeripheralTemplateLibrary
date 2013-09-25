#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <algo/nearptr.hpp>

const int base1 = 0x20000000;
char base2[256] = "foobar";
char *base3 = (char*)malloc(256);

//template <typename T> using Ptr = AbsNearPtr<base1, unsigned short, T>;
template <typename T> using Ptr = ArrayNearPtr<base2, unsigned short, T>;
//template <typename T> using Ptr = VarNearPtr<base3, unsigned short, T>;

void func(Ptr<char> p)
{
    assert(sizeof(p) == 2);
    assert((char*)p == base2 + 3);
    assert(*p == 'b');
    assert(p[1] == 'a');
}

int main()
{
    Ptr<char> p = &base2[3];
    assert(sizeof(p) == 2);
    // Pass into a function to avoid inlining optimizations
    func(p);
}
