#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN

#include "doctest.h"
#include "../MojVektor.hpp"

TEST_CASE(
    "Testing move assignment operator MojVektor<int>& operator=(MojVektor<int>&&)") {
  // Create an original vector
  MojVektor<int> original_v = {1, 2, 3, 4, 5};

  // Create a new vector
  MojVektor<int> new_v;

  // Move the original vector to the new vector
  new_v = std::move(original_v);

  // Check that the size of the original vector is 0
  CHECK(original_v.size() == 0);

  // Check that the capacity of the original vector is 0
  CHECK(original_v.capacity() == 0);

  // Check that the new vector has the correct size
  CHECK(new_v.size() == 5);

  // Check that the new vector has the correct capacity
  CHECK(new_v.capacity() >= 5);

  // Check that the elements in the new vector are correct
  CHECK(new_v[0] == 1);
  CHECK(new_v[1] == 2);
  CHECK(new_v[2] == 3);
  CHECK(new_v[3] == 4);
  CHECK(new_v[4] == 5);
}
