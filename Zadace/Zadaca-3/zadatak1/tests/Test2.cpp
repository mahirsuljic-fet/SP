#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "../DoubleLinkedList.hpp"
#include "doctest.h"

TEST_CASE("empty list returns true") {
  DoubleLinkedList<int> list;
  CHECK(list.empty());
}

TEST_CASE("non-empty list returns false") {
  DoubleLinkedList<int> list;
  list.push_back(1);
  CHECK_FALSE(list.empty());
}
