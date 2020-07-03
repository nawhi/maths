//
// Created by Nick White on 03/07/2020.
//
#include <lazy.h>
#include "catch.hpp"

TEST_CASE("lazy executes the passed function") {
    auto lazy = Lazy([](const double d) { return d + 1; });
    CHECK( lazy(1) == 2 );
}

TEST_CASE("lazy serves result from cache if same result") {
    auto lazy = Lazy([](const double d) { return d + 1; });
    CHECK( lazy(1) == 2 );
    CHECK( lazy(1) == 2 );
}
