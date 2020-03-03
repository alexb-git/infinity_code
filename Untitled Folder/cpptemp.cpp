#include <stdio.h>    /* printf */

extern "C" void Foo(int);

void Foo(int a)
{
        printf("in cpptemp.c | Foo() | %d\n", a);
}
