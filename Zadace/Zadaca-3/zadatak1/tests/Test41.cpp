#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "../DoubleLinkedList.hpp"
#include "doctest.h"

TEST_CASE("Test remove_if function") {
  DoubleLinkedList<int> list;

  // Add some elements to the list
  list.push_back(1).push_back(2).push_back(3).push_back(4);

  // Remove all even elements from the list
  list.remove_if([](const int& x) { return x % 2 == 0; });

  // Check the size of the list
  REQUIRE(list.size() == 2);

  // Check the remaining elements in the list
  auto it = list.begin();
  REQUIRE(*it == 1);
  ++it;
  REQUIRE(*it == 3);
}
