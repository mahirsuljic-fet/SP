#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "../DoubleLinkedList.hpp"
#include "doctest.h"

TEST_CASE("const Iterator rcend function") {
  DoubleLinkedList<int> list;
  list.push_back(1).push_back(2).push_back(3);
  auto it = list.rcend();
  CHECK(it == nullptr);

  // Test rcend function with empty list
  DoubleLinkedList<int> emptyList;
  auto emptyIt = emptyList.rcend();
  CHECK(emptyIt == nullptr);
}
