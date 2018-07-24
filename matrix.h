
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
    Matrix(const Matrix& m);

    std::string str() const;

    // Returns Mij (0-indexed)
    double operator () (int i, int j);

    friend std::ostream& operator << (std::ostream& os, const Matrix& m);
    double operator [] (const int& i) const { return elements[i]; }


private:
    /*
     * Elements read left-to-right from top-left:
     *
     * 0  1  2  3
     * 4  5  6  7
     * 8  9  10 11
     * 12 13 14 15
     *
     * It should really be const but that causes
     * constructor problems
     */
    std::array<double, 16> elements;

};

#endif /* MATRIX_H */