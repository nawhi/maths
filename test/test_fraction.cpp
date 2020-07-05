#include <catch.hpp>
#include <fraction.h>
#include <sstream>

using fractions::greatest_common_divisor, fractions::lowest_common_multiple, fractions::Fraction;

TEST_CASE("greatest_common_divisor") {
    CHECK(greatest_common_divisor<int>(1, 0) == 1);
    CHECK(greatest_common_divisor<int>(1, 1) == 1);
    CHECK(greatest_common_divisor<int>(2, 2) == 2);
    CHECK(greatest_common_divisor<int>(6, 3) == 3);
    CHECK(greatest_common_divisor<int>(8, 12) == 4);
    CHECK(greatest_common_divisor<int>(323, 437) == 19);

}

TEST_CASE("lowest_common_multiple", "[lowest_common_multiple]") {
    CHECK(lowest_common_multiple<int>(1, 1) == 1);
    CHECK(lowest_common_multiple<int>(2, 2) == 2);
    CHECK(lowest_common_multiple<int>(3, 5) == 15);
    CHECK(lowest_common_multiple<int>(39, 13) == 39);
    CHECK(lowest_common_multiple<int>(8, 12) == 24);
}

TEST_CASE("Fraction equality", "[fraction]") {
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
void test_string_repr(Fraction<I> r, const std::string &expected) {
    std::stringstream ss;
    ss << r;
    SECTION(expected) {
        CHECK(ss.str() == expected);
    }
}

TEST_CASE("Fraction stream overload", "[fraction]") {
    test_string_repr<int>(Fraction<int>(1, 2), "1/2");
    test_string_repr<int>(Fraction<int>(2, 4), "1/2");
    test_string_repr<int>(Fraction<int>(1), "1");
    test_string_repr<int>(Fraction<int>(4, 2), "2");
    test_string_repr<long>(Fraction<long>(3000000000L), "3000000000");
}

TEST_CASE("Fraction multiplication", "[fraction]") {
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

TEST_CASE("Fraction division", "[fraction]") {
    SECTION("Fraction / I") {
        CHECK(Fraction<int>(2) / 2 == 1);
        CHECK(Fraction<int>(1, 9) / 9 == Fraction<int>(1, 81));
    }

    SECTION("I / Fraction") {
        CHECK(Fraction<int>(9) / Fraction<int>(9) == Fraction<int>(1));
        CHECK(Fraction<int>(5, 9) / Fraction<int>(3, 8) == Fraction<int>(40, 27));
    }
}

TEST_CASE("Fraction addition", "[fraction]") {
    SECTION("Fraction + Fraction") {
        CHECK(Fraction<int>(1) + Fraction<int>(1) == 2);
        CHECK(Fraction<int>(1, 3) + Fraction<int>(2, 3) == 1);
        CHECK(Fraction<int>(4, 9) + Fraction<int>(7, 13) == Fraction<int>(115, 117));
        CHECK(Fraction<int>(9, 8) + Fraction<int>(10, 9) == Fraction<int>(161, 72));
    }

    SECTION("Fraction + I") {
        CHECK(Fraction<int>(1) + 1 == 2);
        CHECK(Fraction<int>(3, 4) + 2 == Fraction<int>(11, 4));
        CHECK(1 + Fraction<int>(1) == 2);
    }
}

TEST_CASE("Zero fractions", "[fraction]") {
    CHECK_THROWS_AS(Fraction<int>(1, 0), fractions::bad_fraction);
}
