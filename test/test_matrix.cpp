
#include <catch.hpp>
#include <Matrix.h>
#include <lu-decomp.h>


Matrix<int, 4> zero = {
    0, 0, 0, 0,
    0, 0, 0, 0,
    0, 0, 0, 0,
    0, 0, 0, 0
};

Matrix<int, 4> decomp_input = {
    1, 4, 2, 3,
    1, 2, 1, 0,
    0, 0, 1, 2,
    2, 6, 3, 1
};

Matrix<int, 4> lower_diagonal = {
    1, 0, 0, 0,
    1, 1, 0, 0,
    0, 0, 1, 0,
    2, 1, 0, 1,
};

Matrix<int, 4> upper_diagonal = {
    1, 4, 2, 3,
    0, -2, -1, -3,
    0, 0, 1, 2,
    0, 0, 0, -2,
};

template<typename T, int size>
bool is_lower_diag(const Matrix<T, size>& m)
{
    for (int i = 0; i < size; ++i)
        for (int j = 0; j < size; ++j)
            if (i < j && m(i, j) != 0)
                return false;
    return true;
}

template<typename T, int size>
bool is_upper_diag(const Matrix<T, size>& m)
{
    for (int i = 0; i < size; ++i)
        for (int j = 0; j < size; ++j)
            if (i > j && m(i, j) != 0)
                return false;
    return true;
}

TEST_CASE( "is_lower_diag works" )
{
    REQUIRE( is_lower_diag(lower_diagonal) );

    Matrix<double, 2> d = {
        1.5, 0,
        2.5, 3.5
    };
    REQUIRE( is_lower_diag(d) );
}

TEST_CASE( "is_upper_diag works" )
{
    REQUIRE( is_upper_diag(upper_diagonal) );

    Matrix<double, 2> u = {
        1.5, 2.5,
        0,   3.5
    };
    REQUIRE( is_upper_diag(u) );
}

TEST_CASE( "Matrices can be compared for equality" )
{
    auto i = Matrix<int, 4>::identity();
    auto i2 = Matrix<int, 4>::identity();
    REQUIRE( i == i );
    REQUIRE( i == i2 );
    REQUIRE( i != zero );
}

TEST_CASE( "Matrices can be multiplied together" )
{
    auto z = zero;
    REQUIRE( z*z == z );

    auto i = Matrix<int, 4>::identity();
    REQUIRE( i*i == i );

    auto l = lower_diagonal;
    auto u = upper_diagonal;
    REQUIRE( l * u == decomp_input );
}

TEST_CASE( "add_row_multiple works on integer matrices" )
{
    Matrix<int, 4> prev = {
        0,2,4,3,
        2,3,5,4,
        0,0,1,0,
        0,0,0,1
    };
    Matrix<int, 4> post12 = {
        0,2,4,3,
        2,9,17,13,
        0,0,1,0,
        0,0,0,1
    };

    REQUIRE( add_row_multiple(prev, 0, 1, 3) == post12 );

    Matrix<int, 4> post24 = {
        0,2,4,3,
        2,3,5,4,
        0,0,1,0,
        -2,-3,-5,-3
    };

    REQUIRE( add_row_multiple(prev, 1, 3, -1) == post24 );
}

TEST_CASE( "LU decomposition of I works" )
{
    auto res = lu_decomp(Matrix<int, 4>::identity());
    REQUIRE( is_lower_diag(res.first) );
    REQUIRE( is_upper_diag(res.second) );
    REQUIRE( res.first * res.second == Matrix<int, 4>::identity() );
}

TEST_CASE( "LU decomposition of 4x4 integer matrix works" )
{
    /*
     * Problem with using integer matrices to test this
     * is that it requires that the algorithm avoid non-integer
     * division. This shouldn't really be relied upon.
     */
    auto res = lu_decomp(decomp_input);
    REQUIRE( is_lower_diag(res.first) );
    REQUIRE( is_upper_diag(res.second) );
    REQUIRE( res.first * res.second == decomp_input );
}

TEST_CASE( "LU decomposition of 3x3 floating point matrix works" )
{
    Matrix<double, 3> m2 = {
        -5,  3,  4,
        10, -8, -9,
        15,  1,  3
    };
    auto r2 = lu_decomp(m2);
    REQUIRE( is_lower_diag(r2.first) );
    REQUIRE( is_upper_diag(r2.second) );
    REQUIRE( r2.first * r2.second == m2 );
}
