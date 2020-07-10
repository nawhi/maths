
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

namespace matrices::old {


/*
 * A square size * size matrix with elements of type T.
 * T must be a numeric type which is default-constructed
 * to a value of zero and it should support arithmetic and
 * equality operations with integer rvalues.
 */
    template<typename I, int size>
    class Matrix {
    public:
        /*
         * Note that for primitive T this default
         * constructor will return a matrix with
         * uninitialised entries
         * (todo: is this OK: should it return a zero matrix?)
         */
        Matrix<I, size>() = default;

        /*
         * Constructor designed to take matrices in
         * written form in initialiser lists in code.
         */
        Matrix<I, size>(std::initializer_list<I> &&elems);

        /**
         * Constructor designed to take matrices in
         * a 2D vector.
         */
        Matrix<I, size>(std::vector<std::vector<I>> elems);

        static Matrix<I, size> identity();

        /*
         * Zero-indexed getters and setters.
         * operator () is a shorthand for get()
         */
        I operator()(int row, int col) const;

        I get(int row, int col) const;

        void set(int row, int col, I t);


        /*
         * Arithmetic and equality operators
         */

        friend bool operator==(const Matrix &lhs, const Matrix &rhs) {
            return lhs.elements == rhs.elements;
        }

        friend bool operator!=(const Matrix &lhs, const Matrix &rhs) {
            return lhs.elements != rhs.elements;
        }

        friend Matrix operator*(const Matrix &lhs, const Matrix &rhs) {
            Matrix<I, size> ret;
            for (int i = 0; i < size; i++) {
                for (int j = 0; j < size; j++) {
                    I sum = 0;
                    for (int k = 0; k < size; k++)
                        sum += lhs(i, k) * rhs(k, j);
                    ret.set(i, j, sum);
                }
            }
            return ret;
        }

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
        std::array<I, size * size> elements;

        static bool rangecheck(int row, int col) {
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
    template<typename I, int size>
    Matrix<I, size>::Matrix(std::initializer_list<I> &&elems) {
        assert(elems.size() == elements.size());

        for (auto it = elems.begin(); it != elems.end(); ++it) {
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
    template<typename I, int size>
    Matrix<I, size>::Matrix(std::vector<std::vector<I>> v) {
        assert(v.size() == size);
        for (const auto &row: v)
            assert(row.size() == size);

        for (int i = 0; i < size; i++)
            for (int j = 0; j < size; j++)
                elements[size * i + j] = v[j][i];
    }

    template<typename I, int size>
    Matrix<I, size> Matrix<I, size>::identity() {
        Matrix<I, size> m;
        for (int i = 0; i < size; ++i)
            for (int j = 0; j < size; ++j)
                m.set(i, j, (i == j) ? 1 : 0);

        return m;
    }

    template<typename I, int size>
    I Matrix<I, size>::operator()(int row, int col) const {
        assert(rangecheck(row, col));
        return get(row, col);
    }

    template<typename I, int size>
    I Matrix<I, size>::get(int row, int col) const {
        assert(rangecheck(row, col));
        return elements[row + size * col];
    }

    template<typename I, int size>
    void Matrix<I, size>::set(int row, int col, I t) {
        assert(rangecheck(row, col));
        elements[row + size * col] = t;
    }

/*
 * @return a string representation of the matrix.
 * This is separate from operator<< so that it's
 * accessible from the debugger.
 */
    template<typename I, int size>
    std::string Matrix<I, size>::str() const {
        std::stringstream ss;
        for (int i = 0; i < size; i++) {
            ss << "\n[ ";
            for (int j = 0; j < size; j++)
                ss << get(i, j) << " ";
            ss << "]";
        }
        return ss.str();
    }

    template<typename I, int size>
    std::ostream &operator<<(std::ostream &os, const Matrix<I, size> &m) {
        os << m.str();
        return os;
    }

}
#endif /* MATRIX_H */
