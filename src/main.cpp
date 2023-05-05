#include <iostream>
#include "thread.h"

int dummy(int i)
{
    std::cout << i << std::endl;
    return i;
}

int main()
{
    Thread th;

    for(int i=0; i<1000; i++)
        th.add(dummy, i);

    return 0;
}