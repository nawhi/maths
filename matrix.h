
#ifndef MATRIX_H
#define MATRIX_H

#include <iostream>
#include <string>
#include <array>
#include <utility>
#include <cassert>
#include <algorithm>
#include <iterator>
#include <sstream>

/*
 * An immutable 4x4 matrix.
 * T is taken to be a numeric type and
 * must support equality operators == !=,
 * arithmetic operators + - * /,
 * and the stream operator <<
 */
template <typename T>
class Matrix {
public:
    Matrix<T>() = default;
    Matrix<T>(std::initializer_list<T> elems);

    std::string str() const;

    T operator () (int i, int j) const; // 0-indexed
    T operator [] (const int& i) const;

    bool operator == (const Matrix& other) const;
    bool operator != (const Matrix& other) const;

    Matrix<T> operator * (const Matrix<T>& other) const;

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
    std::array<T, 16> elements;

};

template<typename T>
Matrix<T>::Matrix(std::initializer_list<T> elems)
{
    assert(elems.size() == elements.size());
    std::copy(std::begin(elems), std::end(elems), std::begin(elements));
}

template <typename T>
T Matrix<T>::operator () (int i, int j) const
{
    assert(i >= 0 && i < 4 && j >= 0 && j < 4);
    return elements[i + j*4];
}

template <typename T>
T Matrix<T>::operator [] (const int& i) const
{
    return elements[i];
}

template <typename T>
bool Matrix<T>::operator == (const Matrix<T>& other) const
{
    return elements == other.elements;
}

template <typename T>
bool Matrix<T>::operator != (const Matrix<T>& other) const
{
    return elements != other.elements;
}

// this is broken
template <typename T>
Matrix<T> Matrix<T>::operator * (const Matrix<T>& other) const
{
    throw "TODO";
    return other;
}

template<typename T>
std::string Matrix<T>::str() const
{
    /*
     * e.g.
     * [ 1  2  3  4  ]
     * [ 5  6  7  8  ]
     * [ 9  10 11 12 ]
     * [ 13 14 15 16 ]
     */
    std::stringstream ss;
    for (int i = 0; i < 16; i += 4)
    {
        ss << "\n[ ";
        ss << elements[i] << " "
           << elements[i+1] << " "
           << elements[i+2] << " "
           << elements[i+3] << " ]";
    }

    return ss.str();
}

template <typename T>
std::ostream& operator << (std::ostream& os, const Matrix<T>& m)
{
    os << m.str();
    return os;
}

/**
 * Perform an LU-decomposition on any matrix with nonzero
 * pivots.
 * @param mx the input matrix, which must be invertible and
 *        have nonzero pivots
 * @return a std::pair where first is L, and second is U
 */
template <typename T>
std::pair<Matrix<T>, Matrix<T>> lu_decomp(Matrix<T> mx)
{
    std::cout << mx << std::endl;
    throw "Not implemented";
}

#endif /* MATRIX_H */