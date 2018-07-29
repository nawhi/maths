#include <iostream>
#include "matrix.h"
#include "lu-decomp.h"

int main()
{
    std::cout << "Hello world" << std::endl;

    Matrix<int> m{
        1, 2, 3, 4,
        5, 6, 7, 8,
        1, 2, 3, 4,
        5, 6, 7, 8
    };
    std::cout << m << std::endl;
    std::cout << m(0, 0) << std::endl;
    std::cout << m(0, 3) << std::endl;
    // std::cout << m2(0, 4) << std::endl; // Asserts
}
