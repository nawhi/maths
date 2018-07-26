
#include "matrix.h"
#include <algorithm>
#include <iterator>
#include <cstdlib>
#include <sstream>
#include <cassert>

Matrix::Matrix() 
{
    elements.fill(0);
}

Matrix::Matrix(std::initializer_list<double> elems)
{
    assert(elems.size() == elements.size());
    std::copy(std::begin(elems), std::end(elems), std::begin(elements));
}

Matrix Matrix::identity()
{
    return {
        1, 0, 0, 0,
        0, 1, 0, 0,
        0, 0, 1, 0,
        0, 0, 0, 1
    };
}

std::string Matrix::str() const
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
        char buf[64];
        auto fmt = "\n[% -2g% -2g% -2g% -2g ]";
        std::snprintf(buf, 128, fmt, 
            elements[i], elements[i+1],
            elements[i+2], elements[i+3]);
        ss << buf;
    }

    return ss.str();
}

double Matrix::operator () (int i, int j) const
{
    assert(i >= 0 && i < 4 && j >= 0 && j < 4);
    return elements[i + j*4];
}

double Matrix::operator [] (const int& i) const
{
    return elements[i];
}

bool Matrix::operator == (const Matrix& other) const
{
    return elements == other.elements;
}

bool Matrix::operator != (const Matrix& other) const
{
    return elements != other.elements;
}

Matrix Matrix::operator * (const Matrix& other) const
{
    Matrix res;
    for (int i = 0; i < 4; i++)
    {
        for (int j = 0; j < 4; j++)
        {
            int ix = i + 4*j;
            res.elements[ix] = elements[ix] * other[ix];
        }
    }
    return res;
}

std::ostream& operator << (std::ostream& os, const Matrix& m)
{
    os << m.str();
    return os;
}

std::pair<Matrix, Matrix> Matrix::lu_decomp()
{
    throw "Not implemented";
}