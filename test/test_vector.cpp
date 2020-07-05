#include <catch.hpp>
#include <sstream>
#include "Vector.h"
#include "Fraction.h"

using vectors::Vector;
using fractions::Fraction;

TEST_CASE("Illegal vector construction", "[vector]") {
    CHECK_THROWS_AS(Vector<int>({}), vectors::bad_vector);
}

TEST_CASE("Vector equality", "[vector]") {
    CHECK(Vector<int>{1} == Vector<int>{1});
    CHECK(Vector<int>{2} != Vector<int>{1});
}

TEST_CASE("Length of a vector", "[vector]") {
    CHECK(Vector<int>{0}.len() == 0);
    CHECK(Vector<int>{1}.len() == 1);
    CHECK(Vector<int>{2}.len() == 2);
    CHECK(Vector<int>{0, 1}.len() == 1);
    CHECK(Vector<int>{3, 4}.len() == 5);
    CHECK(Vector<int>{2, 3, 6}.len() == 7);

    CHECK(Vector<double>({12., 16., 21.}).len() == 29.);
}

TEST_CASE("Normalizing a vector (set to length 1)", "[vector]") {
    CHECK(Vector<int>{1}.norm() == Vector<int>{1});
    CHECK(Vector<int>{2}.norm() == Vector<int>{1});
    CHECK(Vector<int>{1, 1}.norm() == Vector<int>{1, 1});
    CHECK(Vector<int>{2, 2}.norm() == Vector<int>{1, 1});
    CHECK(Vector<double>({3., 4.}).norm() == Vector<double>{0.6, 0.8});
}

TEST_CASE("Vector stream overload", "[vector]") {
    CHECK((std::stringstream() << Vector<int>{1}).str() == "[1]");
    CHECK((std::stringstream() << Vector<int>{1, 2}).str() == "[1, 2]");

    const auto &vector = Vector<Fraction<int>>{Fraction<int>{1, 2},
                                               Fraction<int>{2, 3},
                                               Fraction<int>{3, 4},
                                               Fraction<int>{4, 5},
                                               Fraction<int>{5, 6}};
    CHECK((std::stringstream() << vector).str() == "[1/2, 2/3, 3/4, 4/5, 5/6]");
}

TEST_CASE("Vector-Vector addition", "[vector]") {
    CHECK_THROWS_AS((Vector<int>{9} + Vector<int>{1, 1}), vectors::dimension_mismatch);

    CHECK(Vector<int>{1} + Vector<int>{1} == Vector<int>{2});
    CHECK((Vector<int>{7, 8, 9} + Vector<int>{1, 2, 1}) == Vector<int>{8, 10, 10});
}

TEST_CASE("Vector-Vector subtraction", "[vector]") {
    CHECK_THROWS_AS((Vector<int>{9} - Vector<int>{1, 1}), vectors::dimension_mismatch);

    CHECK(Vector<int>{1} - Vector<int>{1} == Vector<int>{0});
    CHECK(((Vector<int>{1, 2, 3}) - (Vector<int>{4, 3, 2})) == Vector<int>{-3, -1, 1});
}

TEST_CASE("Vector * Scalar", "[vector]") {
    CHECK(Vector<int>{1, 2, 3} * 2 == Vector<int>{2, 4, 6});
}