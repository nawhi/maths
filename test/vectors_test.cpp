#include "catch.hpp"
#include <vectors.h>
using linalg::vectors::norm;
using linalg::vectors::len;

TEST_CASE("Length of a vector", "[len]") {
    SECTION("1d vector") {
        CHECK(len({0}) == 0);
        CHECK(len({1}) == 1);
        CHECK(len({2}) == 2);
    }

    SECTION("2d vector") {
        CHECK(len({0, 1}) == 1);
        CHECK(len({3, 4}) == 5);
    }

    SECTION("arbitrary length vectors") {
        CHECK(len({2, 3, 6}) == 7);
    }
}

TEST_CASE("Normalizing a vector", "[norm]") {
    SECTION("normalizes a 1d vector") {
        auto v = GENERATE(std::vector<int>{1}, std::vector<int>{2});
        CHECK(norm(v) == std::vector<int>{1});
    }
}