#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "../DoubleLinkedList.hpp"
#include "doctest.h"

TEST_CASE("Iterator assignment operator") {
  DoubleLinkedList<int> list;
  list.push_back(1);
  list.push_back(2);
  list.push_back(3);

  // Get an iterator to the second element of the list
  auto it1 = list.begin();
  ++it1;

  // Create a new iterator and assign it the value of the first iterator
  auto it2 = DoubleLinkedList<int>::Iterator();
  it2 = it1;

  // Check that the new iterator points to the same element as the original
  CHECK(*it2 == 2);

  // Check that advancing one iterator does not affect the other
  ++it1;
  CHECK(*it1 == 3);
  CHECK(*it2 == 2);

  // Check that reassigning the first iterator does not affect the second
  it1 = list.begin();
  CHECK(*it1 == 1);
  CHECK(*it2 == 2);
}
