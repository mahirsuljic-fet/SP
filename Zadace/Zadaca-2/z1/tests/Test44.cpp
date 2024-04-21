#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN

#include "../MojVektor.hpp"
#include "doctest.h"

TEST_CASE("Testing MojVektor::insert(Iterator pos, T&& element)") {
  MojVektor<int> vec{1, 2, 3, 4};

  SUBCASE("Inserting an rvalue at the beginning") {
    auto it = vec.insert(vec.begin(), 0);
    REQUIRE(vec.size() == 5);
    REQUIRE(*it == 0);
    REQUIRE(vec.at(0) == 0);
    REQUIRE(vec.at(1) == 1);
  }

  SUBCASE("Inserting an rvalue in the middle") {
    auto it = vec.insert(vec.begin() + 2, 99);
    REQUIRE(vec.size() == 5);
    REQUIRE(*it == 99);
    REQUIRE(vec.at(0) == 1);
    REQUIRE(vec.at(1) == 2);
    REQUIRE(vec.at(2) == 99);
    REQUIRE(vec.at(3) == 3);
  }

  SUBCASE("Inserting at the end position should throw an exception") {
    REQUIRE_THROWS_AS(vec.insert(vec.end(), 5), std::out_of_range);
  }
}

