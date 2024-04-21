#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN

#include "doctest.h"
#include "../MojVektor.hpp"

TEST_CASE("Get pointer to the vector's data") {
  SUBCASE("Get pointer to non-empty vector's data") {
    MojVektor<int> v{1, 2, 3};
    int* data = v.data();
    CHECK(data[0] == 1);
    CHECK(data[1] == 2);
    CHECK(data[2] == 3);
  }

  SUBCASE("Get pointer to vector with one element's data") {
    MojVektor<int> v{1};
    int* data = v.data();
    CHECK(data[0] == 1);
  }

  SUBCASE("Get pointer to empty vector's data") {
    MojVektor<int> v;
    int* data = v.data();
    CHECK(data != nullptr);
  }
}

