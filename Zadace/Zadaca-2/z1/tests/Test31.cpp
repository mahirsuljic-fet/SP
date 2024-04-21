#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN

#include "doctest.h"
#include "../MojVektor.hpp"

TEST_CASE("MojVektor<int>::begin() returns begin iterator") {
  SUBCASE("Vector is not empty") {
    MojVektor<int> v{1, 2, 3, 4, 5};

    auto iter = v.begin();
    REQUIRE(*iter == 1);
  }

  SUBCASE("Vector is empty") {
    MojVektor<int> v;

    auto iter = v.begin();
    REQUIRE(iter == v.end());
  }
}
