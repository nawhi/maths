
#include "catch.hpp"
#include "../matrix.h"


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

Matrix<int> decomp_l = {
    1, 0, 0, 0,
    1, 1, 0, 0,
    0, 0, 1, 1,
    2, 1, 0, 1,
};

Matrix<int> decomp_u = {
    1, 4, 2, 3,
    0, -2, -1, -3,
    0, 0, 1, 4,
    0, 0, 0, -2,
};

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

    auto res = decomp_l * decomp_u;
    REQUIRE( res == decomp_input );
}

TEST_CASE( "LU decomposition of I and 0 works" )
{
    auto i = identity;
    REQUIRE( lu_decomp(i) == std::make_pair(i, i) );

    auto z = zero;
    REQUIRE( lu_decomp(i) == std::make_pair(z, z) );
}

TEST_CASE( "LU decomposition of simple integer matrix works" )
{
    auto ret = lu_decomp(decomp_input);
    REQUIRE( ret.first == decomp_l );
    REQUIRE( ret.second == decomp_u );
}