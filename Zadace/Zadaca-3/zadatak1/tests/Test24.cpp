#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "../DoubleLinkedList.hpp"
#include "doctest.h"

TEST_CASE("Iterator decrement operator") {
  DoubleLinkedList<int> list;
  list.push_back(1);
  list.push_back(2);
  list.push_back(3);

  // Get an iterator to the last element of the list
  auto it = list.begin();
  ++it;
  ++it;

  // Use the decrement operator and check that the iterator now points to the
  // second element
  --it;
  CHECK(*it == 2);

  // Use the decrement operator again and check that the iterator now points to
  // the first element
  --it;
  CHECK(*it == 1);

  // Use the decrement operator again and check that the iterator is now equal
  // to the end iterator
  --it;
  CHECK(it == list.end());
}
