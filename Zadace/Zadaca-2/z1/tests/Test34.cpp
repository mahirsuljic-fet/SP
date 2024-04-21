#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN

#include "doctest.h"
#include "../MojVektor.hpp"

TEST_CASE("MojVektor<int>::erase() erases correct element and returns iterator to "
          "next element") {

  SUBCASE("Iterator points to first element") {
    MojVektor<int> v{1, 2, 3, 4, 5};
    auto iter = v.erase(v.begin());
    REQUIRE(*iter == 2);
    REQUIRE(v.size() == 4);
    REQUIRE(v[0] == 2);
    REQUIRE(v[1] == 3);
    REQUIRE(v[2] == 4);
    REQUIRE(v[3] == 5);
  }

  SUBCASE("Iterator points to middle element") {
    MojVektor<int> v{1, 2, 3, 4, 5};
    auto iter = v.erase(v.begin() + 2);
    REQUIRE(*iter == 4);
    REQUIRE(v.size() == 4);
    REQUIRE(v[0] == 1);
    REQUIRE(v[1] == 2);
    REQUIRE(v[2] == 4);
    REQUIRE(v[3] == 5);
  }

  SUBCASE("Iterator points to last element") {
    MojVektor<int> v{1, 2, 3, 4, 5};
    auto iter = v.erase(v.end() - 1);
    REQUIRE(iter == v.end());
    REQUIRE(v.size() == 4);
    REQUIRE(v[0] == 1);
    REQUIRE(v[1] == 2);
    REQUIRE(v[2] == 3);
    REQUIRE(v[3] == 4);
  }

  SUBCASE("Iterator points to end") {
    MojVektor<int> v{1, 2, 3, 4, 5};
    auto iter = v.erase(v.end());
    REQUIRE(iter == v.end());
    REQUIRE(v.size() == 5);
    REQUIRE(v[0] == 1);
    REQUIRE(v[1] == 2);
    REQUIRE(v[2] == 3);
    REQUIRE(v[3] == 4);
    REQUIRE(v[4] == 5);
  }
}
