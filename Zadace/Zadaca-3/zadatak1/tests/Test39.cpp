#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "../DoubleLinkedList.hpp"
#include "doctest.h"

TEST_CASE("Erase a node from the list using iterator") {
  DoubleLinkedList<int> list;
  list.push_back(1).push_back(2).push_back(3);

  // Erase the second node
  auto it = list.begin();
  ++it;
  it = list.erase(it);

  // Check that the list contains only the first and third nodes
  REQUIRE(list.size() == 2);
  REQUIRE(list.front() == 1);
  REQUIRE(list.back() == 3);

  // Check that the iterator points to the third node
  REQUIRE(*it == 3);
}
