#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "../DoubleLinkedList.hpp"
#include "doctest.h"

TEST_CASE("Iterator move constructor") {
  DoubleLinkedList<int> list;
  list.push_back(1);
  list.push_back(2);
  list.push_back(3);

  // Get an iterator to the second element of the list
  auto it1 = list.begin();
  ++it1;

  // Move-construct a new iterator from the first iterator
  auto it2 = DoubleLinkedList<int>::Iterator(std::move(it1));

  // Check that the new iterator points to the same element as the original
  CHECK(*it2 == 2);

  // Check that the original iterator is now null
  CHECK(it1.node() == nullptr);
}
