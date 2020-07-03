#include "catch.hpp"
#include <rational.h>
// add
// subtract
// multiply
// divide
// equal
// pow
// gt, ge, lt, le
// ostream

TEST_CASE("gcd (Euclid)", "[gcd]") {
    CHECK(gcd<int>(1, 0) == 1);
    CHECK(gcd<int>(1, 1) == 1);
    CHECK(gcd<int>(2, 2) == 2);
    CHECK(gcd<int>(6, 3) == 3);
    CHECK(gcd<int>(8, 12) == 4);
    CHECK(gcd<int>(323, 437) == 19);
}

TEST_CASE("Rational class equality", "[rational]") {
    CHECK(Rational<int>(1) == Rational<int>(1));
    CHECK(Rational<int>(1, 2) == Rational<int>(1, 2));
    CHECK(Rational<int>(2, 4) == Rational<int>(1, 2));
    CHECK(Rational<int>(14, 26) == Rational<int>(28, 52));
}


