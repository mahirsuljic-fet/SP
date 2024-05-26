#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "../DoubleLinkedList.hpp"
#include "doctest.h"

TEST_CASE("Iterator node function") {
  DoubleLinkedList<int> list;
  list.push_back(1);
  list.push_back(2);
  list.push_back(3);

  // Test node function
  auto it = list.begin();
  CHECK(it.node()->data == 1);

  // Test node function with const iterator
  const auto& constList = list;
  auto cit = constList.begin();
  CHECK(cit.node()->data == 1);
}
