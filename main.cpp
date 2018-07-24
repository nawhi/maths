#include <iostream>

#include "matrix.h"
// #include "matrix.cpp" // linker error otherwise

int main()
{
    std::cout << "Hello world" << std::endl;

    Matrix m;
    std::cout << m << std::endl;

    Matrix m2{
        1, 2, 3, 4,
        5, 6, 7, 8,
        1, 2, 3, 4,
        5, 6, 7, 8
    };
    std::cout << m2 << std::endl;
    std::cout << m2(0, 0) << std::endl;
    std::cout << m2(0, 3) << std::endl;
    std::cout << m2(0, 4) << std::endl;
}
