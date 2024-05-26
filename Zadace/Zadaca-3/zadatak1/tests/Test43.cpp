#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "../DoubleLinkedList.hpp"
#include "doctest.h"

TEST_CASE("find") {
  DoubleLinkedList<int> lst;
  lst.push_back(1).push_back(2).push_back(3);

  SUBCASE("element exists") {
    auto it = lst.find(2);
    REQUIRE(*it == 2);
  }

  SUBCASE("element doesn't exist") {
    auto it = lst.find(4);
    REQUIRE(it == lst.end());
  }
}
