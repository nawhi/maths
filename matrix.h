
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
#include <vector>

/*
 * An 4x4 matrix.
 * Type T must support equality operators == !=,
 * arithmetic operators + - * /,
 * unary operators + -,
 * and the stream operator <<
 */
template <typename T>
class Matrix {
public:
    Matrix<T>() = default;
    Matrix<T>(std::initializer_list<T> elems);
    Matrix<T>(std::vector<std::vector<T>> elems);

    /*
     * Zero-indexed getters and setters.
     * operator () is a shorthand for get()
     */
    T operator () (int row, int col) const;
    T get(int row, int col) const;
    void set(int row, int col, T t);

    
    /*
     * Arithmetic and equality operators 
     */

    template <typename U>
    friend bool operator == (const Matrix<U>& lhs, const Matrix<U>& rhs);
    
    template <typename U>
    friend bool operator != (const Matrix<U>& lhs, const Matrix<U>& rhs);

    template <typename U>
    friend Matrix<U> operator * (const Matrix<U>& lhs, const Matrix<U>& rhs);

    /**
     * Method for converting matrix to a string. (Useful for debuggers)
     * @return a string representation of the matrix
     */
    std::string str() const;

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

    static bool rangecheck(int row, int col)
    {
        return row >= 0 && row < 4 && col >= 0 && col < 4;
    }

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

/**
 * Constructor designed to take matrices in a
 * vector of four vectors:
 *
 * v[0][0] v[0][1] v[0][2] v[0][3]
 * v[1][0] v[1][1] v[1][2] v[1][3]
 * v[2][0] v[2][1] v[2][2] v[2][3]
 * v[3][0] v[3][1] v[3][2] v[3][3]
 */
template<typename T>
Matrix<T>::Matrix(std::vector<std::vector<T>> v)
{
    assert(v.size() == 4);
    for(const auto& row: v)
        assert(row.size() == 4);
        
    for (int i = 0; i < 4; i++)
        for (int j = 0; j < 4; j++)
            elements[4*i + j] = v[j][i];
}

template <typename T>
T Matrix<T>::operator () (int row, int col) const
{
    assert(rangecheck(row, col));
    return get(row, col);
}

template <typename T>
T Matrix<T>::get(int row, int col) const
{ 
    assert(rangecheck(row, col));
    return elements[row + 4*col]; 
}

template <typename T>
void Matrix<T>::set(int row, int col, T t) 
{
    assert(rangecheck(row, col));
    elements[row + 4*col] = t;
}

template <typename T>
bool operator == (const Matrix<T>& lhs, const Matrix<T>& rhs)
{
    return lhs.elements == rhs.elements;
}

template <typename T>
bool operator != (const Matrix<T>& lhs, const Matrix<T>& rhs)
{
    return lhs.elements != rhs.elements;
}

template <typename T>
Matrix<T> operator * (const Matrix<T>& lhs, const Matrix<T>& rhs)
{
    Matrix<T> ret;
    for (int i = 0; i < 4; i++)
    {
        for (int j = 0; j < 4; j++)
        {
            T sum = 0;
            for (int k = 0; k < 4; k++)
                sum += lhs(i, k) * rhs(k, j);
            ret.set(i, j, sum);
        }
    }
    return ret;
}

template<typename T>
std::string Matrix<T>::str() const
{
    std::stringstream ss;
    for (int i = 0; i < 4; i++)
    {
        ss << "\n[ ";
        for (int j = 0; j < 4; j++)
            ss << get(i, j) << " ";
        ss << "]";
    }
    return ss.str();
}

template <typename T>
std::ostream& operator << (std::ostream& os, const Matrix<T>& m)
{
    os << m.str();
    return os;
}

#endif /* MATRIX_H */
