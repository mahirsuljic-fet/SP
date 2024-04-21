#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN

#include "../MojVektor.hpp"
#include "doctest.h"

TEST_CASE("Resize vector") {
  MojVektor<int> v{1, 2, 3};

  SUBCASE("Resizing to a smaller size") {
    v.resize(2, 0);
    CHECK(v.size() == 2);
    CHECK(v.capacity() >= 3); // Capacity should remain the same
    CHECK(v[0] == 1);
    CHECK(v[1] == 2);
  }

  SUBCASE("Resizing to a larger size") {
    v.resize(5, 10);
    CHECK(v.size() == 5);
    CHECK(v.capacity() >= 5); // Capacity should be increased if necessary
    CHECK(v[0] == 1);
    CHECK(v[1] == 2);
    CHECK(v[2] == 3);
    CHECK(v[3] == 10);
    CHECK(v[4] == 10);
  }

  SUBCASE("Resizing to the same size") {
    v.resize(3, -2);
    CHECK(v.size() == 3);
    CHECK(v.capacity() >= 3); // Capacity should remain the same
    CHECK(v[0] == 1);
    CHECK(v[1] == 2);
    CHECK(v[2] == 3);
  }
}

