#include <catch.hpp>
#include <sstream>
#include <complex.h>
#include "Vector.h"
#include "Fraction.h"

using vectors::Vector;
using fractions::Fraction;

TEST_CASE("Illegal vector construction", "[vector]") {
    CHECK_THROWS_AS(Vector<int>({}), vectors::bad_vector);
}

TEST_CASE("Vector::zero", "[vector]") {
    CHECK(Vector<int>::zero(3) == Vector<int>{0, 0, 0});
    CHECK(Vector<int>::zero(9) == Vector<int>{0, 0, 0, 0, 0, 0, 0, 0, 0});
    CHECK_THROWS_AS(Vector<int>::zero(0), vectors::bad_vector);
}

TEST_CASE("Vector equality", "[vector]") {
    CHECK(Vector<int>{1} == Vector<int>{1});
    CHECK(Vector<int>{2} != Vector<int>{1});
}

TEST_CASE("Length of a vector", "[vector]") {
    CHECK(Vector<double>{0}.length() == 0);
    CHECK(Vector<double>{1}.length() == 1);
    CHECK(Vector<double>{2}.length() == 2);
    CHECK(Vector<double>{0, 1}.length() == 1);
    CHECK(Vector<double>{3, 4}.length() == 5);
    CHECK(Vector<double>{2, 3, 6}.length() == 7);

    CHECK(Vector<double>({12., 16., 21.}).length() == 29.);
}

TEST_CASE("Normalizing a vector (set to length 1)", "[vector]") {
    CHECK(Vector<double>{1}.norm() == Vector<double>{1});
    CHECK(Vector<double>{2}.norm() == Vector<double>{1});
    CHECK(Vector<double>({3, 4}).norm() == Vector<double>{0.6, 0.8});
}

TEST_CASE("Vector stream overload", "[vector]") {
    CHECK((std::stringstream() << Vector<int>{1}).str() == "[1]");
    CHECK((std::stringstream() << Vector<int>{1, 2}).str() == "[1 2]");

    const auto &vector = Vector<Fraction<int>>{Fraction<int>{1, 2},
                                               Fraction<int>{2, 3},
                                               Fraction<int>{3, 4},
                                               Fraction<int>{4, 5},
                                               Fraction<int>{5, 6}};
    CHECK((std::stringstream() << vector).str() == "[1/2 2/3 3/4 4/5 5/6]");
}

TEST_CASE("Vector + Vector", "[vector]") {
    CHECK_THROWS_AS((Vector<int>{9} + Vector<int>{1, 1}), vectors::dimension_mismatch);

    CHECK(Vector<int>{1} + Vector<int>{1} == Vector<int>{2});
    CHECK((Vector<int>{7, 8, 9} + Vector<int>{1, 2, 1}) == Vector<int>{8, 10, 10});
}

TEST_CASE("Vector - Vector", "[vector]") {
    CHECK_THROWS_AS((Vector<int>{9} - Vector<int>{1, 1}), vectors::dimension_mismatch);

    CHECK(Vector<int>{1} - Vector<int>{1} == Vector<int>{0});
    CHECK(((Vector<int>{1, 2, 3}) - (Vector<int>{4, 3, 2})) == Vector<int>{-3, -1, 1});
}

TEST_CASE("Vector * Scalar", "[vector]") {
    CHECK(Vector<int>{1, 2, 3} * 2 == Vector<int>{2, 4, 6});
    CHECK(Vector<double>{50., 50.} * (1. / 2) == Vector<double>{25., 25.});
}

TEST_CASE("Vector / Scalar", "[vector]") {
    CHECK(Vector<int>{2, 4, 6} / 2 == Vector<int>{1, 2, 3});
}

TEST_CASE("Vector dot Vector", "[vector]") {
    CHECK(Vector<int>{1}.dot({1}) == 1);
    CHECK(Vector<int>{1, 2}.dot({2, 5}) == 12);
    CHECK(Vector<int>{-3, -4}.dot({5, -2}) == -7);

}

TEST_CASE("Vector cross Vector", "[vector]") {
    SECTION("is undefined for non-3d vectors") {
        CHECK_THROWS_AS(Vector<int>{1}.cross({1}), vectors::dimension_mismatch);
        CHECK_THROWS_AS((Vector<int>{1, 2, 3, 4}.cross({1, 2})), vectors::dimension_mismatch);
    }

    CHECK(Vector<int>{1, 1, 1}.cross({1, 1, 1}) == Vector<int>{0, 0, 0});
    CHECK(Vector<int>{1, 0, 0}.cross({0, 0, 1}) == Vector<int>{0, -1, 0});
    CHECK(Vector<int>{3, 4, 5}.cross({5, 4, 3}) == Vector<int>{-8, 16, -8});
}

TEST_CASE("Vector project Vector", "[vector]") {
    CHECK_THROWS_AS((Vector<int>{1, 2, 3, 4}.project(Vector<int>{1, 2})), vectors::dimension_mismatch);

    CHECK(Vector<int>{1, 1}.project({1, 1}) == Vector<int>{1, 1});
    CHECK(Vector<double>{2, 3, 4, 5}.project({4, 6, 8, 10}) == Vector<double>{2, 3, 4, 5});
    CHECK(Vector<int>{17, -7}.project({12, 5}) == Vector<int>{12, 5});
    CHECK(Vector<double>{12, 5}.project({17, -7}) == Vector<double>{8.5, -3.5});
}

TEST_CASE("Vector angle_to Vector is clockwise angle from v1 to v2", "[vector]") {
    CHECK_THROWS_AS((Vector<double>{1, 2, 3, 4}.angle_to(Vector<double>{1, 2})), vectors::dimension_mismatch);

//    CHECK(Vector<double>{1, 1}.angle_to({1, 1}) == Approx(0)); // TODO why does this fail?
    CHECK(std::abs(Vector<double>{1, 1}.angle_to({1, 1})) < 0.00001);
    CHECK(Vector<double>{1, 1}.angle_to({-1, -1}) == Approx(M_PI));
    CHECK(Vector<double>{0.2, 0.2}.angle_to({-0.2, -0.2}) == Approx(M_PI));
}