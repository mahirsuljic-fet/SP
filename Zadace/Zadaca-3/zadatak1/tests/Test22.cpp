#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "../DoubleLinkedList.hpp"
#include "doctest.h"

TEST_CASE("Iterator prefix increment operator") {
  DoubleLinkedList<int> list;
  list.push_back(1);
  list.push_back(2);
  list.push_back(3);

  // Get an iterator to the first element of the list
  auto it = list.begin();

  // Increment the iterator and check that it points to the second element
  ++it;
  CHECK(*it == 2);

  // Increment the iterator again and check that it points to the third element
  ++it;
  CHECK(*it == 3);

  // Increment the iterator again and check that it is equal to the end iterator
  ++it;
  CHECK(it == list.end());
}
