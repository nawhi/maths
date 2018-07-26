
#include "catch.hpp"
#include "../matrix.h"

TEST_CASE( "Sanity check" )
{
    Matrix m;
    REQUIRE( true );
}

TEST_CASE( "Matrices can be compared for equality")
{
    auto i = Matrix::identity();
    auto i2 = Matrix::identity();
    REQUIRE( i == i2 );
    REQUIRE( i != Matrix{} );
}

TEST_CASE( "Matrices can be multiplied together")
{
    auto i = Matrix::identity();
    REQUIRE( i*i == i );
    
    Matrix zero;
    REQUIRE( zero*zero == Matrix{} );

}