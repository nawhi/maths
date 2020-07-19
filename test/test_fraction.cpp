#include <catch.hpp>
#include <sstream>
#include <cmath>
#include "Fraction.h"

using fractions::greatest_common_divisor, fractions::lowest_common_multiple, fractions::Fraction;

TEST_CASE("greatest_common_divisor") {
    CHECK(greatest_common_divisor(1, 0) == 1);
    CHECK(greatest_common_divisor(1, 1) == 1);
    CHECK(greatest_common_divisor(2, 2) == 2);
    CHECK(greatest_common_divisor(6, 3) == 3);
    CHECK(greatest_common_divisor(8, 12) == 4);
    CHECK(greatest_common_divisor(323, 437) == 19);
    CHECK(greatest_common_divisor(LONG_MAX, LONG_MAX) == LONG_MAX);
}

TEST_CASE("lowest_common_multiple", "[lowest_common_multiple]") {
    CHECK(lowest_common_multiple(1, 1) == 1);
    CHECK(lowest_common_multiple(2, 2) == 2);
    CHECK(lowest_common_multiple(3, 5) == 15);
    CHECK(lowest_common_multiple(39, 13) == 39);
    CHECK(lowest_common_multiple(8, 12) == 24);
    CHECK(lowest_common_multiple(LONG_MAX, LONG_MAX) == LONG_MAX);
}

TEST_CASE("Fraction no-args constructor is zero", "[Fraction]") {
    CHECK(Fraction<int>() == 0);
}

TEST_CASE("Fraction can be explicitly and implicitly cast to double", "[Fraction]") {
    CHECK((double) Fraction(1, 2) == Approx(0.5));

    double d = Fraction(1, 7);
    CHECK(d == Approx(0.142857).epsilon(0.00001));
}

TEST_CASE("Fraction equality", "[fraction]") {
    SECTION("Fraction == Fraction") {
        CHECK(Fraction(1) == Fraction(1));
        CHECK(Fraction(2) == Fraction(2));
        CHECK(Fraction(1, 2) == Fraction(1, 2));
        CHECK(Fraction(2, 4) == Fraction(1, 2));
        CHECK(Fraction(14, 26) == Fraction(28, 52));
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

TEST_CASE("Fraction stream overload", "[fraction]") {
    CHECK((std::stringstream() << Fraction<int>(1, 2)).str() == "1/2");
    CHECK((std::stringstream() << Fraction<int>(2, 4)).str() == "1/2");
    CHECK((std::stringstream() << Fraction<int>(1)).str() == "1");
    CHECK((std::stringstream() << Fraction<int>(4, 2)).str() == "2");
    CHECK((std::stringstream() << Fraction<long>(3000000000L)).str() == "3000000000");
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

    SECTION("Unary plus") {
        CHECK(Fraction<int>(1) == +Fraction<int>(1));
    }
}

TEST_CASE("Fraction subtraction", "[fraction]") {
    SECTION("Fraction - Fraction") {
        CHECK(Fraction<int>(2) - Fraction<int>(1) == 1);
        CHECK(Fraction<int>(1, 2) - Fraction<int>(1, 4) == Fraction<int>(1, 4));
        CHECK(Fraction<int>(7, 9) - Fraction<int>(4, 13) == Fraction<int>(55, 117));
        CHECK(Fraction<int>(3, 9) - Fraction<int>(5, 9) == Fraction<int>(-2, 9));
    }

    SECTION("Fraction - I") {
        CHECK(Fraction<int>(1) - 1 == 0);
        CHECK(Fraction<int>(3, 9) - 2 == Fraction<int>(-15, 9));
    }

    SECTION("Unary minus") {
        CHECK(Fraction<int>(-1) == -Fraction<int>(1));
    }
}

TEST_CASE("Fraction inequalities", "[fraction]") {
    CHECK(Fraction<int>(2) > Fraction<int>(1));
    CHECK(Fraction<int>(4, 3) > Fraction<int>(5, 4));
    CHECK(Fraction<int>(2) >= Fraction<int>(2));
    CHECK(Fraction<int>(2, 3) >= Fraction<int>(1, 3));

    CHECK(Fraction<int>(2) > 1);
    CHECK(Fraction<int>(2) >= 2);
    CHECK(Fraction<int>(2) >= 1);

    CHECK(2 > Fraction<int>(1));
    CHECK(2 >= Fraction<int>(2));
    CHECK(2 >= Fraction<int>(1));

    CHECK(Fraction<int>(1) < Fraction<int>(2));
    CHECK(Fraction<int>(5, 4) < Fraction<int>(4, 3));
    CHECK(Fraction<int>(2) <= Fraction<int>(2));
    CHECK(Fraction<int>(1, 3) <= Fraction<int>(2, 3));

    CHECK(1 < Fraction<int>(2));
    CHECK(2 <= Fraction<int>(2));
    CHECK(1 <= Fraction<int>(2));

    CHECK(Fraction<int>(1) < 2);
    CHECK(Fraction<int>(2) <= 2);
    CHECK(Fraction<int>(1) <= 2);
}


TEST_CASE("Zero fractions", "[fraction]") {
    CHECK_THROWS_AS(Fraction<int>(1, 0), fractions::division_by_zero);
    const Fraction<int> &zero = Fraction<int>(0);
    CHECK(zero == 0);
    CHECK(zero / 1 == 0);
    CHECK(zero * zero == 0);
    CHECK_THROWS_AS(zero / zero, fractions::division_by_zero);
}

TEST_CASE("Fraction square root", "[fraction]") {
    CHECK(sqrt(Fraction<int>{2, 3}) == Approx(0.8164965809277));
}

