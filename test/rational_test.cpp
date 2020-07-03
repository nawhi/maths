#include "catch.hpp"
#include <rational.h>
#include <sstream>

// to do:
// add
// subtract
// multiply
// divide
// equal
// pow
// gt, ge, lt, le
// cast to floating point
// cast to int(?)

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

    CHECK(Rational<int>(1, 2) != Rational<int>(2, 1));

    SECTION("implicit conversions") {
        CHECK(Rational<int>(1) == 1);
        CHECK(Rational<int>(1, 1) == 1);
        CHECK(Rational<int>(2, 4) != 2);
    }
}

void test_string_repr(Rational<int> r, const std::string& expected) {
    std::stringstream ss;
    ss << r;
    CHECK(ss.str() == expected);
}
TEST_CASE("Rational class string representation", "[rational]") {
    test_string_repr(Rational<int>(1, 2), "1/2");
    test_string_repr(Rational<int>(2, 4), "1/2");
    test_string_repr(Rational<int>(1), "1");
    test_string_repr(Rational<int>(4, 2), "2");
}

//TEST_CASE("Adding Rationals") {
    // Rational + Rational
    // Rational + int
    // int + Rational
    // Rational += Rational
    // Rational += int
    // int += Rational (?)
//}

