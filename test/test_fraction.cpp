#include "catch.hpp"
#include <fraction.h>
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

TEST_CASE("gcd", "[gcd]") {
    CHECK(gcd<int>(1, 0) == 1);
    CHECK(gcd<int>(1, 1) == 1);
    CHECK(gcd<int>(2, 2) == 2);
    CHECK(gcd<int>(6, 3) == 3);
    CHECK(gcd<int>(8, 12) == 4);
    CHECK(gcd<int>(323, 437) == 19);
}

TEST_CASE("Fraction equality", "[rational]") {
    SECTION("Fraction == Fraction") {
        CHECK(Fraction<int>(1) == Fraction<int>(1));
        CHECK(Fraction<int>(1, 2) == Fraction<int>(1, 2));
        CHECK(Fraction<int>(2, 4) == Fraction<int>(1, 2));
        CHECK(Fraction<int>(14, 26) == Fraction<int>(28, 52));
    }

    SECTION("Fraction != Fraction") {
        CHECK(Fraction<int>(1, 2) != Fraction<int>(2, 1));
    }

    SECTION("Fraction<I> == I") {
        CHECK(Fraction<int>(1) == 1);
        CHECK(1 == Fraction<int>(1));

        CHECK(Fraction<int>(1, 1) == 1);
        CHECK(Fraction<int>(2, 4) != 2);

        CHECK(Fraction<long>(LONG_MAX) == LONG_MAX);
        CHECK(LONG_MAX == Fraction<long>(LONG_MAX));
    }

    SECTION("Fraction<I> != I") {
        CHECK(Fraction<int>(1) != 2);
        CHECK(LONG_MAX != Fraction<long>(LONG_MAX, 2));
    }
}

template<typename I>
void test_string_repr(Fraction<I> r, const std::string& expected) {
    std::stringstream ss;
    ss << r;
    CHECK(ss.str() == expected);
}
TEST_CASE("Fraction stream overload", "[rational]") {
    test_string_repr<int>(Fraction<int>(1, 2), "1/2");
    test_string_repr<int>(Fraction<int>(2, 4), "1/2");
    test_string_repr<int>(Fraction<int>(1), "1");
    test_string_repr<int>(Fraction<int>(4, 2), "2");
    test_string_repr<long>(Fraction<long>(3000000000L), "3000000000");
}

//TEST_CASE("Adding Rationals") {
    // Fraction + Fraction
    // Fraction + int
    // int + Fraction
    // Fraction += Fraction
    // Fraction += int
    // int += Fraction (?)
//}

