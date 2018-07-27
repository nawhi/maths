
#include "catch.hpp"
#include "../matrix.h"


Matrix<int> zero()
{
    return {
        0, 0, 0, 0,
        0, 0, 0, 0,
        0, 0, 0, 0,
        0, 0, 0, 0
    };
}

Matrix<int> identity()
{
    return {
        1, 0, 0, 0,
        0, 1, 0, 0,
        0, 0, 1, 0,
        0, 0, 0, 1
    };
}

TEST_CASE( "Matrices can be compared for equality" )
{
    auto i = identity();
    auto i2 = identity();
    REQUIRE( i == i );
    REQUIRE( i == i2 );
    REQUIRE( i != zero() );
}

TEST_CASE( "Matrices can be multiplied together" )
{
    auto z = zero();
    REQUIRE( z*z == z );

    auto i = identity();
    REQUIRE( i*i == i );

}

TEST_CASE( "LU decomposition of I and 0 works" )
{
    auto i = identity();
    REQUIRE( lu_decomp(i) == std::make_pair(i, i) );

    auto z = zero();
    REQUIRE( lu_decomp(i) == std::make_pair(z, z) );
}

TEST_CASE( "LU decomposition of simple integer matrix works" )
{
    // todo
}