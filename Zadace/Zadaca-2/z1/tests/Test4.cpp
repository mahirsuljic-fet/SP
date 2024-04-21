#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN

#include "doctest.h"
#include "../MojVektor.hpp"

TEST_CASE(
    "Testing copy assignment operator MojVektor<int>& operator=(const MojVektor<int>&)") {
  // Create an original vector
  MojVektor<int> original_v = {1, 2, 3, 4, 5};

  // Create a new vector
  MojVektor<int> new_v;

  // Assign the original vector to the new vector
  new_v = original_v;

  // Check that the sizes of both vectors are equal
  CHECK(original_v.size() == new_v.size());

  // Check that the capacities of both vectors are equal
  CHECK(original_v.capacity() == new_v.capacity());

  // Check that all elements in the new vector are equal to the elements in the
  // original vector
  for (size_t i = 0; i < original_v.size(); i++) {
    CHECK(original_v[i] == new_v[i]);
  }
}

