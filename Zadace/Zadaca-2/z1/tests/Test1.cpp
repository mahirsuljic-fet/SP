#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN

#include "doctest.h"
#include "../MojVektor.hpp"

TEST_CASE("Testing default constructor MojVektor<int>()") {
  MojVektor<int> v;

  // Check that the size of the vector is 0
  CHECK(v.size() == 0);

  // Check that the capacity of the vector is 10
  CHECK(v.capacity() == 10);

  // Check that the vector is empty
  CHECK(v.empty() == true);
}

