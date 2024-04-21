#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN

#include "../MojVektor.hpp"
#include "doctest.h"

TEST_CASE("MojVektor subvector testing") {
  // Create a vector with some test data.
  MojVektor<int> testData = {1, 2, 3, 4, 5};

  MojVektor<int> v;
  for (int i : testData) {
    v.push_back(i);
  }

  SUBCASE("Get the subvector from the beginning to the end") {
    MojVektor<int> subvec = v.subvector(v.begin(), v.end());
    REQUIRE(subvec.size() == 5);
    for (int i = 0; i < subvec.size(); ++i) {
      REQUIRE(subvec[i] == testData[i]);
    }
  }

  SUBCASE("Get the subvector from the middle to the end") {
    MojVektor<int> subvec = v.subvector(v.begin() + 2, v.end());
    REQUIRE(subvec.size() == 3);
    for (int i = 0; i < subvec.size(); ++i) {
      REQUIRE(subvec[i] == testData[i + 2]);
    }
  }

  SUBCASE("Get the subvector from the beginning to the middle") {
    MojVektor<int> subvec = v.subvector(v.begin(), v.begin() + 3);
    REQUIRE(subvec.size() == 3);
    for (int i = 0; i < subvec.size(); ++i) {
      REQUIRE(subvec[i] == testData[i]);
    }
  }

  SUBCASE("Get the empty subvector") {
    MojVektor<int> subvec = v.subvector(v.begin(), v.begin());
    REQUIRE(subvec.size() == 0);
  }
}
