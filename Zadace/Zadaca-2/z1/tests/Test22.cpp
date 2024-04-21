#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN

#include "doctest.h"
#include "../MojVektor.hpp"

TEST_CASE("MojVektor<int> full") {
  MojVektor<int> v;

  SUBCASE("When the vector is full, the full method should return true") {
    for (int i = 0; i < 10; ++i) {
      v.push_back(i);
    }
    CHECK(v.full() == true);
  }

  SUBCASE("When the vector is not full, the full method should return false") {
    for (int i = 0; i < 4; ++i) {
      v.push_back(i);
    }
    CHECK(v.full() == false);
  }

  SUBCASE("When the vector is empty, the full method should return false") {
    CHECK(v.full() == false);
  }
}

