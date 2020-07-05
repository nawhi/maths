#include <catch.hpp>
#include "Vector.h"

TEST_CASE("Vector equality", "[vector]") {
    CHECK(Vector<int>({1}) == Vector<int>({1}));
    CHECK(Vector<int>({2}) != Vector<int>({1}));
}

TEST_CASE("Length of a vector", "[vector]") {
    CHECK(Vector<int>({0}).len() == 0);
    CHECK(Vector<int>({1}).len() == 1);
    CHECK(Vector<int>({2}).len() == 2);
    CHECK(Vector<int>({0, 1}).len() == 1);
    CHECK(Vector<int>({3, 4}).len() == 5);
    CHECK(Vector<int>({2, 3, 6}).len() == 7);

    CHECK(Vector<double>({12., 16., 21.}).len() == 29.);
}

TEST_CASE("Normalizing a vector sets it to length 1", "[vector]") {
    CHECK(Vector<int>({1}).norm() == Vector<int>{1});
    CHECK(Vector<int>({2}).norm() == Vector<int>{1});
    CHECK(Vector<int>({1, 1}).norm() == Vector<int>{1, 1});
    CHECK(Vector<int>({2, 2}).norm() == Vector<int>{1, 1});
    CHECK(Vector<double>({3., 4.}).norm() == Vector<double>{0.6, 0.8});
}