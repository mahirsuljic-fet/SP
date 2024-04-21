#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN

#include "../MojVektor.hpp"
#include "doctest.h"

TEST_CASE("Testing MojVektor::push_front(T&&)") {
  MojVektor<int> vec;

  SUBCASE("Pushing front a single rvalue") {
    vec.push_front(1);
    REQUIRE(vec.size() == 1);
    REQUIRE(vec.front() == 1);
  }

  SUBCASE("Pushing front multiple rvalues") {
    vec.push_front(1);
    vec.push_front(2);
    vec.push_front(3);
    REQUIRE(vec.size() == 3);
    REQUIRE(vec.front() == 3);
    REQUIRE(vec.at(1) == 2);
    REQUIRE(vec.at(2) == 1);
  }
}
