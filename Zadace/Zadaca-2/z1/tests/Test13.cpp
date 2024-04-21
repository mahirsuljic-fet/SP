#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN

#include "doctest.h"
#include "../MojVektor.hpp"

TEST_CASE("Testing clear() method") {
  // Create a vector with some elements
  MojVektor<int> v = {1, 2, 3};

  // Check that the size of the vector is 3
  CHECK(v.size() == 3);

  // Clear the vector
  v.clear();
  // arr_ pointer is nullptr
  CHECK(v.data() == nullptr);

  // Check that the size of the vector is now 0
  CHECK(v.size() == 0);

  // Add new elements to the vector
  v.push_back(4);
  v.push_back(5);

  // Check that the size of the vector is 2
  CHECK(v.size() == 2);
}

