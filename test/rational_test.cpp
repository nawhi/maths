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

TEST_CASE("Fraction class equality", "[rational]") {
    CHECK(Fraction<int>(1) == Fraction<int>(1));
    CHECK(Fraction<int>(1, 2) == Fraction<int>(1, 2));
    CHECK(Fraction<int>(2, 4) == Fraction<int>(1, 2));
    CHECK(Fraction<int>(14, 26) == Fraction<int>(28, 52));

    CHECK(Fraction<int>(1, 2) != Fraction<int>(2, 1));

    SECTION("implicit conversions") {
        CHECK(Fraction<int>(1) == 1);
        CHECK(Fraction<int>(1, 1) == 1);
        CHECK(Fraction<int>(2, 4) != 2);
    }
}

void test_string_repr(Fraction<int> r, const std::string& expected) {
    std::stringstream ss;
    ss << r;
    CHECK(ss.str() == expected);
}
TEST_CASE("Fraction class string representation", "[rational]") {
    test_string_repr(Fraction<int>(1, 2), "1/2");
    test_string_repr(Fraction<int>(2, 4), "1/2");
    test_string_repr(Fraction<int>(1), "1");
    test_string_repr(Fraction<int>(4, 2), "2");
}

//TEST_CASE("Adding Rationals") {
    // Fraction + Fraction
    // Fraction + int
    // int + Fraction
    // Fraction += Fraction
    // Fraction += int
    // int += Fraction (?)
//}

