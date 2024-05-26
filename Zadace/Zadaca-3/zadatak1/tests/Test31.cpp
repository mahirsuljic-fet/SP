#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "../DoubleLinkedList.hpp"
#include "doctest.h"

TEST_CASE("Iterator begin function") {
  DoubleLinkedList<int> list;
  list.push_back(1);
  list.push_back(2);
  list.push_back(3);

  // Test begin function
  auto it = list.begin();
  CHECK(*it == 1);

  // Test begin function with empty list
  DoubleLinkedList<int> emptyList;
  auto emptyIt = emptyList.begin();
  CHECK(emptyIt == emptyList.end());
}
