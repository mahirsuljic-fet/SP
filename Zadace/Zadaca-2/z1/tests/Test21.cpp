#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN

#include "doctest.h"
#include "../MojVektor.hpp"

TEST_CASE("Output the vector to a stream") {
  SUBCASE("Output non-empty vector") {
    MojVektor<int> v{1, 2, 3};
    std::ostringstream oss;
    oss << v;
    CHECK(oss.str() == "{1, 2, 3}");
  }

  SUBCASE("Output vector with one element") {
    MojVektor<int> v{1};
    std::ostringstream oss;
    oss << v;
    CHECK(oss.str() == "{1}");
  }

  SUBCASE("Output empty vector") {
    MojVektor<int> v;
    std::ostringstream oss;
    oss << v;
    CHECK(oss.str() == "{}");
  }
}

