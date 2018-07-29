
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
 * An 4x4 matrix which is publicly immutable.
 * Type T must support equality operators == !=,
 * arithmetic operators + - * /,
 * and the stream operator <<
 */
template <typename T>
class Matrix {
public:
    Matrix<T>() = default;
    Matrix<T>(std::initializer_list<T> elems);

    std::string str() const;

    T operator () (int row, int col) const; // 0-indexed

    bool operator == (const Matrix& other) const;
    bool operator != (const Matrix& other) const;

    Matrix<T> operator * (const Matrix<T>& rhs) const;

private:
    /*
     * Internally, elements read from top-left 
     * in columns, OpenGL style:
     *
     * 0  4  8  12
     * 1  5  9  13
     * 2  6  10 14
     * 3  7  11 15
     */
    std::array<T, 16> elements;

    T get(int row, int col) const { return elements[row + 4*col]; }
    void set(int row, int col, T t) { elements[row + 4*col] = t; }
};

/**
 * Constructor designed to take matrices in written form:
 *
 * 0  1  2  3
 * 4  5  6  7
 * 8  9  10 11
 * 12 13 14 15 
 */
template<typename T>
Matrix<T>::Matrix(std::initializer_list<T> elems)
{
    assert(elems.size() == elements.size());

    for (auto it = elems.begin(); it != elems.end(); ++it)
    {
        int ix = it - elems.begin();
        set(ix / 4, ix % 4, *it);
    }
}

template <typename T>
T Matrix<T>::operator () (int row, int col) const
{
    assert(row >= 0 && row < 4 && col >= 0 && col < 4);
    return get(row, col);
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

template <typename T>
Matrix<T> Matrix<T>::operator * (const Matrix<T>& rhs) const
{
    Matrix<T> ret;
    for (int i = 0; i < 4; i++)
    {
        for (int j = 0; j < 4; j++)
        {
            T sum = 0;
            for (int k = 0; k < 4; k++)
                sum += get(i, k) * rhs.get(k, j);
            ret.set(i, j, sum);
        }
    }
    return ret;
}

template <typename T>
std::ostream& operator << (std::ostream& os, const Matrix<T>& m)
{
    for (int i = 0; i < 4; i++)
    {
        os << "\n[ ";
        for (int j = 0; j < 4; j++)
            os << m(i, j) << " ";
        os << "]";
    }
    return os;
}

#endif /* MATRIX_H */
