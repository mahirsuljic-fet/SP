#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN

#include "doctest.h"
#include "../MojVektor.hpp"

TEST_CASE("Testing size() function") {
  // Create an empty vector
  MojVektor<int> v;

  // Check that the size of the vector is 0
  CHECK(v.size() == 0);

  // Add elements to the vector
  v.push_back(1);
  v.push_back(2);
  v.push_back(3);

  // Check that the size of the vector is now 3
  CHECK(v.size() == 3);

  // Clear the vector and check that the size is 0 again
  v.clear();
  CHECK(v.size() == 0);
}

