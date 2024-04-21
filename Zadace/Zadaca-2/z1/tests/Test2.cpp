#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN

#include "doctest.h"
#include "../MojVektor.hpp"

TEST_CASE("Testing constructor MojVektor<int>(const std::initializer_list<int>&)") {
  MojVektor<int> v = {1, 2, 3, 4, 5};

  // Check that the size of the vector is equal to the number of elements in the
  // initializer list
  CHECK(v.size() == 5);

  // Check that the elements of the vector are equal to the elements in the
  // initializer list
  CHECK(v[0] == 1);
  CHECK(v[1] == 2);
  CHECK(v[2] == 3);
  CHECK(v[3] == 4);
  CHECK(v[4] == 5);
}
