#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "../DoubleLinkedList.hpp"
#include "doctest.h"

TEST_CASE("const Iterator rcbegin function") {
  DoubleLinkedList<int> list;
  list.push_back(1).push_back(2).push_back(3);
  auto it = list.rcbegin();
  CHECK(*it == 3);

  // Test rcbegin function with empty list
  const DoubleLinkedList<int> emptyList;
  auto emptyIt = emptyList.rcbegin();
  CHECK(emptyIt == nullptr);
}
