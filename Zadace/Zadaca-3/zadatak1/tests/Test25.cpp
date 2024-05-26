#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "../DoubleLinkedList.hpp"
#include "doctest.h"

TEST_CASE("Iterator post-decrement operator") {
  DoubleLinkedList<int> list;
  list.push_back(1);
  list.push_back(2);
  list.push_back(3);

  // Get an iterator to the last element of the list
  auto it = list.begin();
  ++it;
  ++it;

  // Use the post-decrement operator and check that the iterator still points to
  // the last element
  auto it2 = it--;
  CHECK(*it2 == 3);
  CHECK(*it == 2);

  // Use the post-decrement operator again and check that the iterator still
  // points to the second element
  it2 = it--;
  CHECK(*it2 == 2);
  CHECK(*it == 1);
  CHECK(it == list.begin());

  // Use the post-decrement operator again and check that the iterator still
  // points to the first element
  it2 = it--;
  CHECK(*it2 == 1);
}
