#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "../DoubleLinkedList.hpp"
#include "doctest.h"

TEST_CASE("Iterator node constructor") {
  DoubleLinkedList<int> list;
  list.push_back(1);
  list.push_back(2);
  list.push_back(3);

  // Get an iterator to the second element of the list
  auto it1 = list.begin();
  ++it1;

  // Create a new iterator from the node pointed to by the first iterator
  auto it2 = DoubleLinkedList<int>::Iterator(it1.node());

  // Check that the new iterator points to the same element as the original
  CHECK(*it2 == 2);

  // Check that the two iterators are the same
  CHECK(&(*it1) == &(*it2));

  // Check that advancing one iterator does not affect the other
  ++it1;
  CHECK(*it1 == 3);
  CHECK(*it2 == 2);
}
