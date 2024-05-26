#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "../DoubleLinkedList.hpp"
#include "doctest.h"

TEST_CASE("Iterator rbegin function") {
  DoubleLinkedList<int> list;
  list.push_back(1).push_back(2).push_back(3);
  auto it = list.rbegin();
  CHECK(*it == 3);

  // Test rbegin function with empty list
  DoubleLinkedList<int> emptyList;
  auto emptyIt = emptyList.rbegin();
  CHECK(emptyIt == nullptr);
}
