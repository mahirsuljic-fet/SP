#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN

#include "doctest.h"
#include "../MojVektor.hpp"

TEST_CASE("Testing at() method with valid index") {
  // Create a vector with some elements
  MojVektor<int> v = {1, 2, 3};

  // Access a valid element using the at() method
  CHECK(v.at(1) == 2);
}

