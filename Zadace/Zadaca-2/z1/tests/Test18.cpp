#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN

#include "doctest.h"
#include "../MojVektor.hpp"

TEST_CASE("Get capacity of vector") {
  SUBCASE("Get capacity of non-empty vector") {
    MojVektor<int> v{1, 2, 3};
    CHECK(v.capacity() >= 3);
  }

  SUBCASE("Get capacity of vector with one element") {
    MojVektor<int> v{1};
    CHECK(v.capacity() >= 1);
  }

  SUBCASE("Get capacity of empty vector") {
    MojVektor<int> v;
    CHECK(v.capacity() >= 0);
  }
}

