#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "../DoubleLinkedList.hpp"
#include "doctest.h"

TEST_CASE("Iterator postfix increment operator") {
  DoubleLinkedList<int> list;
  list.push_back(1);
  list.push_back(2);
  list.push_back(3);

  // Get an iterator to the first element of the list
  auto it = list.begin();

  // Use the postfix increment operator and check that the original iterator is
  // unchanged
  auto old_it = it++;
  CHECK(*old_it == 1);

  // Check that the new iterator points to the second element
  CHECK(*it == 2);

  // Use the postfix increment operator again and check that the original
  // iterator is unchanged
  old_it = it++;
  CHECK(*old_it == 2);

  // Check that the new iterator points to the third element
  CHECK(*it == 3);

  // Use the postfix increment operator again and check that the original
  // iterator is unchanged
  old_it = it++;
  CHECK(*old_it == 3);

  // Check that the new iterator is equal to the end iterator
  CHECK(it == list.end());
}
