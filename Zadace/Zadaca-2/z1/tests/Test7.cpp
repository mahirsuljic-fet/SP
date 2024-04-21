#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN

#include "doctest.h"
#include "../MojVektor.hpp"

TEST_CASE("Testing destructor ~MojVektor<int>()") {
  // Create a vector
  MojVektor<int> v = {1, 2, 3, 4, 5};

  // Get the pointer to the internal array of the vector
  int* arr_ptr = v.data();

  // Call the destructor explicitly
  v.~MojVektor<int>();

  // Check that the size of the vector is 0
  CHECK(v.size() == 0);

  // Check that the capacity of the vector is 0
  CHECK(v.capacity() == 0);

  // Check that the internal array pointer is still valid
  CHECK(arr_ptr != nullptr);
}
