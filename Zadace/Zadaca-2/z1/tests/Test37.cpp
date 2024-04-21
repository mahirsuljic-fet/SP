#include <iostream>
#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN

#include "doctest.h"
#include "../MojVektor.hpp"

TEST_CASE("MojVektor<int>::erase() erases correct elements in range and returns "
          "iterator to next element") {
  MojVektor<int> v{1, 2, 3, 4, 5, 6, 7, 8};

  SUBCASE("Erasing first half of vector") {
    auto iter = v.erase(v.begin(), v.begin() + 4);
    REQUIRE(*iter == 5);
    REQUIRE(v.size() == 4);
    REQUIRE(v[0] == 5);
    REQUIRE(v[1] == 6);
    REQUIRE(v[2] == 7);
    REQUIRE(v[3] == 8);
  }

  SUBCASE("Erasing second half of vector") {
    auto iter = v.erase(v.begin() + 4, v.end());
    REQUIRE(iter == v.end());
    REQUIRE(v.size() == 4);
    REQUIRE(v[0] == 1);
    REQUIRE(v[1] == 2);
    REQUIRE(v[2] == 3);
    REQUIRE(v[3] == 4);
  }

  SUBCASE("Erasing entire vector") {
    auto iter = v.erase(v.begin(), v.end());
    REQUIRE(iter == v.end());
    REQUIRE(v.empty());
  }
}
