#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "../DoubleLinkedList.hpp"
#include "doctest.h"

TEST_CASE("Test reverse() method") {
  DoubleLinkedList<int> l;
  l.push_back(1).push_back(2).push_back(3).push_back(4);

  l.reverse();

  REQUIRE(l.size() == 4);
  REQUIRE(l.front() == 4);
  REQUIRE(l.back() == 1);

  auto it = l.begin();
  REQUIRE(*it == 4);
  ++it;
  REQUIRE(*it == 3);
  ++it;
  REQUIRE(*it == 2);
  ++it;
  REQUIRE(*it == 1);
}
