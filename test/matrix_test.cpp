
#include "catch.hpp"
#include "../matrix.h"
#include "../lu-decomp.h"


Matrix<int> zero = {
    0, 0, 0, 0,
    0, 0, 0, 0,
    0, 0, 0, 0,
    0, 0, 0, 0
};

Matrix<int> identity = {
    1, 0, 0, 0,
    0, 1, 0, 0,
    0, 0, 1, 0,
    0, 0, 0, 1
};

Matrix<int> decomp_input = {
    1, 4, 2, 3,
    1, 2, 1, 0,
    0, 0, 1, 2,
    2, 6, 3, 1
};

Matrix<int> lower_diagonal = {
    1, 0, 0, 0,
    1, 1, 0, 0,
    0, 0, 1, 0,
    2, 1, 0, 1,
};

Matrix<int> upper_diagonal = {
    1, 4, 2, 3,
    0, -2, -1, -3,
    0, 0, 1, 2,
    0, 0, 0, -2,
};

bool is_lower_diag(const Matrix<int>& m)
{
    const auto ones = { m(0,0), m(1,1), m(2,2), m(3,3) };
    const auto zeroes = { 
        m(0,1), m(0,2), m(0,3), m(1,2), m(1,3), m(2,3)
    };

    return 
        std::all_of(std::begin(ones), std::end(ones),
            [](const auto& i) { return i == 1; })
        && std::all_of(std::begin(zeroes), std::end(zeroes),
            [](const auto& i) { return i == 0; });
}

bool is_upper_diag(const Matrix<int>& m)
{
    const auto zeroes = {
        m(1,0), m(2,0), m(3,0), m(2,1), m(3,1), m(3,2)
    };
    return std::all_of(std::begin(zeroes), std::end(zeroes),
        [](const auto& i) { return i == 0; });
}

TEST_CASE( "is_lower_diag works" )
{
    REQUIRE( is_lower_diag(lower_diagonal) );
}

TEST_CASE( "is_upper_diag works" )
{
    REQUIRE( is_upper_diag(upper_diagonal) );
}

TEST_CASE( "Matrices can be compared for equality" )
{
    auto i = identity;
    auto i2 = identity;
    REQUIRE( i == i );
    REQUIRE( i == i2 );
    REQUIRE( i != zero );
}

TEST_CASE( "Matrices can be multiplied together" )
{
    auto z = zero;
    REQUIRE( z*z == z );

    auto i = identity;
    REQUIRE( i*i == i );

    auto l = lower_diagonal;
    auto u = upper_diagonal;
    REQUIRE( l * u == decomp_input );
}

TEST_CASE( "add_row_multiple works on integer matrices" )
{
    Matrix<int> prev = {
	0,2,4,3,
	2,3,5,4,
	0,0,1,0,
	0,0,0,1
    };
    Matrix<int> post12 = {
    	0,2,4,3,
    	2,9,17,13,
    	0,0,1,0,
    	0,0,0,1
    };

    REQUIRE( add_row_multiple(prev, 0, 1, 3) == post12 );

    Matrix<int> post24 = {
	0,2,4,3,
	2,3,5,4,
	0,0,1,0,
	-2,-3,-5,-3
    };

    REQUIRE( add_row_multiple(prev, 1, 3, -1) == post24 );
}

TEST_CASE( "LU decomposition of I works" )
{
    auto res = lu_decomp(identity);
    REQUIRE( is_lower_diag(res.first) );
    REQUIRE( is_upper_diag(res.second) );
    REQUIRE( res.first * res.second == identity );
}

TEST_CASE( "LU decomposition of simple integer matrix works" )
{
    /*
     * Problem with using integer matrices to test this
     * is that it requires that the algorithm avoid non-integer
     * division. This shouldn't really be relied upon.
     */
    auto res = lu_decomp(decomp_input);
    REQUIRE( is_lower_diag(res.first) );
    std::cout << res.first << std::endl;
    std::cout << res.second << std::endl;
    REQUIRE( is_upper_diag(res.second) );
    REQUIRE( res.first * res.second == decomp_input );
}
