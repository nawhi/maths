#include "catch.hpp"
#include <fraction.h>
#include <sstream>

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
        CHECK(Fraction<int>(2) == Fraction<int>(2));
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

TEST_CASE("Fraction multiplication") {
    SECTION("Fraction * I") {
        CHECK(Fraction<int>(1) * 2 == 2);
        CHECK(Fraction<int>(4, 3) * 3 == 4);
        CHECK(Fraction<int>(3, 8) * 4 == Fraction<int>(3, 2));
        CHECK(2 * Fraction<int>(1) == 2);
    }

    SECTION("Fraction * Fraction") {
        CHECK(Fraction<int>(4) * Fraction<int>(2) == 8);
        CHECK(Fraction<int>(2, 8) * Fraction<int>(3, 5) == Fraction<int>(3, 20));
    }
}

TEST_CASE("Fraction division") {
    SECTION("Fraction / I") {
        CHECK(Fraction<int>(2) / 2 == 1);
        CHECK(Fraction<int>(1, 9) / 9 == Fraction<int>(1, 81));
    }

    SECTION("I / Fraction") {
        CHECK(Fraction<int>(9) / Fraction<int>(9) == Fraction<int>(1));
        CHECK(Fraction<int>(5, 9) / Fraction<int>(3, 8) == Fraction<int>(40, 27));
    }
}

