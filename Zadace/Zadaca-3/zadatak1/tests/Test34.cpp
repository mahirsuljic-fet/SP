#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "../DoubleLinkedList.hpp"
#include "doctest.h"

TEST_CASE("const Iterator cend function") {
  DoubleLinkedList<int> list;
  list.push_back(1).push_back(2).push_back(3);

  // Test cend function
  auto it = list.cend();
  CHECK(it == nullptr);

  // Test cend function with non-empty list
  auto beginIt = list.cbegin();
  auto endIt = list.cend();
  CHECK(beginIt != endIt);

  // Test cend function with empty list
  const DoubleLinkedList<int> emptyList;
  auto emptyIt = emptyList.cend();
  CHECK(emptyIt == nullptr);
}
