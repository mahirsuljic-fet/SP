#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "../DoubleLinkedList.hpp"
#include "doctest.h"

TEST_CASE("Iterator insert function") {
  DoubleLinkedList<int> list;
  list.push_back(1).push_back(2).push_back(3).push_back(4);

  // Test inserting at the beginning
  auto it = list.begin();
  auto newIt = list.insert(it, 0);
  CHECK(*newIt == 0);
  CHECK(list.size() == 5);
  CHECK(list.front() == 0);

  // Test inserting in the middle
  it = list.begin();
  std::advance(it, 2);
  newIt = list.insert(it, 5);
  CHECK(*newIt == 5);
  CHECK(list.size() == 6);

  // Test inserting into an empty list
  DoubleLinkedList<int> emptyList;
  auto emptyIt = emptyList.insert(emptyList.begin(), 1);
  CHECK(*emptyIt == 1);
  CHECK(emptyList.size() == 1);
}
