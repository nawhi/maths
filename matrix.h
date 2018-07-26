
#ifndef MATRIX_H
#define MATRIX_H

#include <iostream>
#include <string>
#include <array>
#include <utility>

/**
 * An immutable 4x4 matrix
 */
class Matrix {
public:
    Matrix();
    Matrix(std::initializer_list<double> elems);
    static Matrix identity();

    std::string str() const;

    double operator () (int i, int j) const; // 0-indexed
    double operator [] (const int& i) const;

    bool operator == (const Matrix& other) const;
    bool operator != (const Matrix& other) const;

    Matrix operator * (const Matrix& other) const;

    friend std::ostream& operator << (std::ostream& os, const Matrix& m);
    
    // Returns the LU-decomposition of the matrix:
    // the diagonals of L are always 1
    std::pair<Matrix, Matrix> lu_decomp();


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