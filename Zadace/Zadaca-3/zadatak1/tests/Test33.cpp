#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "../DoubleLinkedList.hpp"
#include "doctest.h"

TEST_CASE("Iterator end function") {
  DoubleLinkedList<int> list;
  list.push_back(1);
  list.push_back(2);
  list.push_back(3);

  // Test end function
  auto it = list.end();
  CHECK(it == nullptr);

  // Test end function with non-empty list
  auto beginIt = list.begin();
  auto endIt = list.end();
  CHECK(beginIt != endIt);

  // Test end function with empty list
  DoubleLinkedList<int> emptyList;
  auto emptyIt = emptyList.end();
  CHECK(emptyIt == nullptr);
}
