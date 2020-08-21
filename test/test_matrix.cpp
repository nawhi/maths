#include <sstream>

#include <catch.hpp>
#include "Matrix.h"

using namespace matrices;

TEST_CASE("Matrix construction", "[matrix]") {
    CHECK_THROWS_AS(Matrix<int>{}, bad_matrix);
}

TEST_CASE("Matrix streaming", "[matrix]") {
    Matrix<int> mx = {{1, 2},
                      {3, 4}};

    const auto s = (std::ostringstream() << mx).str();
    CHECK(s == "[1 2]\n[3 4]");

    Matrix<double> mx2 = {{1, 2, 3},
                          {4, 5, 6},
                          {7, 8, 9}};

    const auto s2 = (std::ostringstream() << mx2).str();
    CHECK(s2 == "[1 2 3]\n[4 5 6]\n[7 8 9]");
}

TEST_CASE("Matrix equality", "[matrix]") {
    CHECK(Matrix<int>{{1, 2}, {3, 4}} == Matrix<int>{{1, 2}, {3, 4}});
    CHECK(Matrix<int>{{3, 4}, {1, 2}} != Matrix<int>{{1, 2}, {3, 4}});
}

TEST_CASE("Matrix + Matrix", "[matrix]") {
    CHECK(Matrix<int>{{1, 2}, {3, 4}} + Matrix<int>{{1, 1}, {1, 1}} == Matrix<int>{{2, 3}, {4, 5}});
}

