#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN

#include "doctest.h"
#include "../MojVektor.hpp"

TEST_CASE("Pop element from back of vector") {
  SUBCASE("Pop element from non-empty vector") {
    MojVektor<int> v{1, 2, 3};
    v.pop_back();
    CHECK(v.size() == 2);
    CHECK(v[0] == 1);
    CHECK(v[1] == 2);
  }

  SUBCASE("Pop element from vector with one element") {
    MojVektor<int> v{1};
    v.pop_back();
    CHECK(v.size() == 0);
    CHECK_THROWS_AS(v.pop_back(), std::out_of_range);
  }

  SUBCASE("Pop element from empty vector") {
    MojVektor<int> v;
    CHECK_THROWS_AS(v.pop_back(), std::out_of_range);
  }
}

