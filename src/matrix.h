
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
 * A square size * size matrix with elements of type T.
 * T must be a numeric type which is implicitly
 * convertible from int (so that the correct
 * identity matrix can be formed).
 * It should also support:
 *    the equality operators == !=
 *    the arithmetic operators + - * /
 *    the unary operators + -
 *    the stream operator <<
 */
template <typename T, int size>
class Matrix {
public:
    /*
     * Note that for primitive T this default
     * constructor will return a matrix with
     * uninitialised entries
     * (todo: is this OK: should it return a zero matrix?)
     */
    Matrix<T, size>() = default;
    
    /*
     * Constructor designed to take matrices in 
     * written form in initialiser lists in code.
     */
    Matrix<T, size>(std::initializer_list<T> elems);

    /**
     * Constructor designed to take matrices in 
     * a 2D vector.
     */
    Matrix<T, size>(std::vector<std::vector<T>> elems);

    static Matrix<T, size> identity();

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

    template <typename U, int sz>
    friend bool operator == (const Matrix<U, sz>& lhs, const Matrix<U, sz>& rhs);
    
    template <typename U, int sz>
    friend bool operator != (const Matrix<U, sz>& lhs, const Matrix<U, sz>& rhs);

    template <typename U, int sz>
    friend Matrix<U, sz> operator * (const Matrix<U, sz>& lhs, const Matrix<U, sz>& rhs);

    /**
     * Method for converting matrix to a string. (Useful for debuggers)
     * @return a string representation of the matrix
     */
    std::string str() const;

private:
    /*
     * Internally, elements read from top-left 
     * in columns, OpenGL style. E.g. (for a 4x4 matrix):
     *
     * 0  4  8  12
     * 1  5  9  13
     * 2  6  10 14
     * 3  7  11 15
     */
    std::array<T, size*size> elements;

    static bool rangecheck(int row, int col)
    {
        return row >= 0 && row < size && col >= 0 && col < size;
    }

};

/*
 * Constructor designed to take matrices in 'written' form
 * in an initialiser list.
 * E.g. (for a 4x4 matrix):
 *
 * 0  1  2  3
 * 4  5  6  7
 * 8  9  10 11
 * 12 13 14 15 
 */
template<typename T, int size>
Matrix<T, size>::Matrix(std::initializer_list<T> elems)
{
    assert(elems.size() == elements.size());

    for (auto it = elems.begin(); it != elems.end(); ++it)
    {
        int ix = it - elems.begin();
        set(ix / size, ix % size, *it);
    }
}

/*
 * Constructor designed to take matrices in a
 * 2D vector. E.g. (for a 4x4 matrix):
 *
 * v[0][0] v[0][1] v[0][2] v[0][3]
 * v[1][0] v[1][1] v[1][2] v[1][3]
 * v[2][0] v[2][1] v[2][2] v[2][3]
 * v[3][0] v[3][1] v[3][2] v[3][3]
 */
template<typename T, int size>
Matrix<T, size>::Matrix(std::vector<std::vector<T>> v)
{
    assert(v.size() == size);
    for(const auto& row: v)
        assert(row.size() == size);
        
    for (int i = 0; i < size; i++)
        for (int j = 0; j < size; j++)
            elements[size*i + j] = v[j][i];
}

template <typename T, int size>
Matrix<T, size> Matrix<T, size>::identity()
{
    Matrix<T,size> m;
    for (int i = 0; i < size; ++i)
        for (int j = 0; j < size; ++j)
            m.set(i, j, (i==j) ? 1 : 0);

    return m;
}

template <typename T, int size>
T Matrix<T, size>::operator () (int row, int col) const
{
    assert(rangecheck(row, col));
    return get(row, col);
}

template <typename T, int size>
T Matrix<T, size>::get(int row, int col) const
{ 
    assert(rangecheck(row, col));
    return elements[row + size*col]; 
}

template <typename T, int size>
void Matrix<T, size>::set(int row, int col, T t) 
{
    assert(rangecheck(row, col));
    elements[row + size*col] = t;
}

template <typename T, int size>
bool operator == (const Matrix<T, size>& lhs, const Matrix<T, size>& rhs)
{
    return lhs.elements == rhs.elements;
}

template <typename T, int size>
bool operator != (const Matrix<T, size>& lhs, const Matrix<T, size>& rhs)
{
    return lhs.elements != rhs.elements;
}

template <typename T, int size>
Matrix<T, size> operator * (const Matrix<T, size>& lhs, const Matrix<T, size>& rhs)
{
    Matrix<T, size> ret;
    for (int i = 0; i < size; i++)
    {
        for (int j = 0; j < size; j++)
        {
            T sum = 0;
            for (int k = 0; k < size; k++)
                sum += lhs(i, k) * rhs(k, j);
            ret.set(i, j, sum);
        }
    }
    return ret;
}

/*
 * @return a string representation of the matrix.
 * This is separate from operator<< so that it's
 * accessible from the debugger.
 */
template<typename T, int size>
std::string Matrix<T, size>::str() const
{
    std::stringstream ss;
    for (int i = 0; i < size; i++)
    {
        ss << "\n[ ";
        for (int j = 0; j < size; j++)
            ss << get(i, j) << " ";
        ss << "]";
    }
    return ss.str();
}

template <typename T, int size>
std::ostream& operator << (std::ostream& os, const Matrix<T, size>& m)
{
    os << m.str();
    return os;
}

#endif /* MATRIX_H */
