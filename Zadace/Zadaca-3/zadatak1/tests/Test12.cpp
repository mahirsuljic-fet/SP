#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "../DoubleLinkedList.hpp"
#include "doctest.h"

TEST_CASE("copy constructor creates new list with same elements") {
  DoubleLinkedList<int> list1;
  list1.push_back(1);
  list1.push_back(2);
  list1.push_back(3);

  DoubleLinkedList<int> list2(list1);

  CHECK(list1.size() == list2.size());
  CHECK(list1.front() == list2.front());
  CHECK(list1.back() == list2.back());
}

TEST_CASE("copy constructor creates new list with independent memory") {
  DoubleLinkedList<int> list1;
  list1.push_back(1);
  list1.push_back(2);
  list1.push_back(3);

  DoubleLinkedList<int> list2(list1);

  list1.pop_front();
  list1.push_front(0);

  CHECK(list1.size() == 3);
  CHECK(list2.size() == 3);
  CHECK(list1.front() == 0);
  CHECK(list2.front() == 1);
  CHECK(list1.back() == 3);
  CHECK(list2.back() == 3);
}
