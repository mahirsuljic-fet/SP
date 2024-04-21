#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN

#include "doctest.h"
#include "../MojVektor.hpp"

TEST_CASE("Get last element of vector") {
  SUBCASE("Get last element of non-empty vector") {
    MojVektor<int> v{1, 2, 3};
    CHECK(v.back() == 3);
  }

  SUBCASE("Get last element of vector with one element") {
    MojVektor<int> v{1};
    CHECK(v.back() == 1);
  }

  SUBCASE("Get last element of empty vector") {
    MojVektor<int> v;
    CHECK_THROWS_AS(v.back(), std::out_of_range);
  }
}
