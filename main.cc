#include <iostream>

#include "mdlog.h"

int main()
{
    std::cout << "Hello, World!" << std::endl;

    MDINFO("test", "Hello, World!");

    return 0;
}