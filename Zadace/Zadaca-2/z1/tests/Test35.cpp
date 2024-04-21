#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN

#include "doctest.h"
#include "../MojVektor.hpp"

TEST_CASE("MojVektor<int>::insert() inserts element at correct position and returns "
          "modified vector") {
  MojVektor<int> v{1, 2, 4, 5};

  SUBCASE("Inserting element at beginning of vector") {
    auto iter = v.insert(v.begin(), 0);
    REQUIRE(v.size() == 5);
    REQUIRE(*iter == 0);
    REQUIRE(v[0] == 0);
    REQUIRE(v[1] == 1);
    REQUIRE(v[2] == 2);
    REQUIRE(v[3] == 4);
    REQUIRE(v[4] == 5);
  }

  SUBCASE("Inserting element in middle of vector") {
    auto iter = v.insert(v.begin() + 2, 3);
    REQUIRE(v.size() == 5);
    REQUIRE(*iter == 3);
    REQUIRE(v[0] == 1);
    REQUIRE(v[1] == 2);
    REQUIRE(v[2] == 3);
    REQUIRE(v[3] == 4);
    REQUIRE(v[4] == 5);
  }

  SUBCASE("Inserting element at end of vector") {
    REQUIRE_THROWS_AS(v.insert(v.end(), 6), std::out_of_range);
    REQUIRE(v.size() == 4);
    REQUIRE(v[0] == 1);
    REQUIRE(v[1] == 2);
    REQUIRE(v[2] == 4);
    REQUIRE(v[3] == 5);
  }
}
