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

TEST_CASE("Rational class construction", "[rational]") {
    CHECK(Rational<int>(1) == Rational<int>(1));
}

