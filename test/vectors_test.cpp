#include "catch.hpp"
#include <vectors.h>
using linalg::vectors::norm;
using linalg::vectors::len;

TEST_CASE("Length of a vector", "[len]") {
        CHECK(len<int>({0}) == 0);
        CHECK(len<int>({1}) == 1);
        CHECK(len<int>({2}) == 2);
        CHECK(len<int>({0, 1}) == 1);
        CHECK(len<int>({3, 4}) == 5);
        CHECK(len<int>({2, 3, 6}) == 7);

        CHECK(len<double>({12., 16., 21.}) == 29.);
}

TEST_CASE("Normalizing a vector", "[norm]") {
    SECTION("normalizes a 1d vector") {
        auto v = GENERATE(std::vector<int>{1}, std::vector<int>{2});
        CHECK(norm(v) == std::vector<int>{1});
    }
}