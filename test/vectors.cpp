#include "catch.hpp"
#include <vectors.h>
using linalg::vectors::norm;
using linalg::vectors::len;

TEST_CASE("Length of a vector", "[len]") {
    SECTION("length of a 1d vector") {
        CHECK(len({1}) == 1);
        CHECK(len({2}) == 2);
    }
}

TEST_CASE("Normalizing a vector", "[norm]") {
    SECTION("normalizes a 1d vector") {
        auto v = GENERATE(std::vector<int>{1}, std::vector<int>{2});
        CHECK(norm(v) == std::vector<int>{1});
    }
}