#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN

#include "doctest.h"
#include "../MojVektor.hpp"

TEST_CASE("Testing operator[] with in-bounds and out-of-bounds indexing") {
  // Create a vector with some elements
  MojVektor<int> v = {1, 2, 3};

  // Access in-bounds elements using the [] operator
  CHECK(v[0] == 1);
  CHECK(v[1] == 2);
  CHECK(v[2] == 3);

  // Try to access out-of-bounds elements using the [] operator
  // This could lead to undefined behavior
  int i = v[3];  // DON'T DO THIS! Accessing an out-of-bounds index could lead
                 // to undefined behavior
}
