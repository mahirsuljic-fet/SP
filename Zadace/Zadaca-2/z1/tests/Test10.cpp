#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN

#include "doctest.h"
#include "../MojVektor.hpp"

TEST_CASE("Testing at() method with out of bounds indexing") {
  // Create a vector with some elements
  MojVektor<int> v = {1, 2, 3};

  // Try to access an element outside of the vector using the at() method
  CHECK_THROWS_AS(v.at(5), std::out_of_range);
}

