
#ifndef MATRIX_H
#define MATRIX_H

#include <iostream>
#include <string>
#include <array>

/**
 * An immutable 4x4 matrix
 */
class Matrix {
public:
    Matrix();
    Matrix(std::initializer_list<double> elems);

    friend std::ostream& operator << (std::ostream& os, const Matrix& m);
    double operator [] (const int& i) const { return elements[i]; }

    std::string str() const;

private:
    std::array<double, 16> elements;

};

#endif /* MATRIX_H */