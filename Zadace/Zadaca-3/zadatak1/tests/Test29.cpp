#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "../DoubleLinkedList.hpp"
#include "doctest.h"

TEST_CASE("Iterator dereference operator") {
  DoubleLinkedList<int> list;
  list.push_back(1);
  list.push_back(2);
  list.push_back(3);

  // Test dereference operator
  auto it = list.begin();
  CHECK(*it == 1);

  // Test dereference operator with const iterator
  const auto& constList = list;
  auto cit = constList.begin();
  CHECK(*cit == 1);
}
