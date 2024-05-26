#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "../DoubleLinkedList.hpp"
#include "doctest.h"

TEST_CASE("copy assignment operator copies elements from source list") {
  DoubleLinkedList<int> list1;
  list1.push_back(1);
  list1.push_back(2);
  list1.push_back(3);

  DoubleLinkedList<int> list2;
  list2.push_back(4);
  list2.push_back(5);
  list2.push_back(6);

  list2 = list1;

  CHECK(list1.size() == 3);
  CHECK(list1.front() == 1);
  CHECK(list1.back() == 3);
  CHECK(list2.size() == 3);
  CHECK(list2.front() == 1);
  CHECK(list2.back() == 3);
}

TEST_CASE("copy assignment operator creates new list with independent memory") {
  DoubleLinkedList<int> list1;
  list1.push_back(1);
  list1.push_back(2);
  list1.push_back(3);

  DoubleLinkedList<int> list2;
  list2.push_back(4);
  list2.push_back(5);
  list2.push_back(6);

  list2 = list1;

  list1.pop_front();
  list1.push_front(0);

  CHECK(list1.size() == 3);
  CHECK(list2.size() == 3);
  CHECK(list1.front() == 0);
  CHECK(list2.front() == 1);
  CHECK(list1.back() == 3);
  CHECK(list2.back() == 3);
}

TEST_CASE("copy assignment operator handles self-assignment") {
  DoubleLinkedList<int> list;
  list.push_back(1);
  list.push_back(2);
  list.push_back(3);

  list = list;

  CHECK(list.size() == 3);
  CHECK(list.front() == 1);
  CHECK(list.back() == 3);
}

TEST_CASE("copy assignment operator returns a reference to the list") {
  DoubleLinkedList<int> list1;
  DoubleLinkedList<int> list2;

  DoubleLinkedList<int>& list1Ref = (list1 = list2);

  CHECK(&list1Ref == &list1);
  CHECK(&list1Ref != &list2);
}

TEST_CASE("copy assignment operator handles empty source list") {
  DoubleLinkedList<int> list1;
  list1.push_back(1);
  list1.push_back(2);
  list1.push_back(3);

  DoubleLinkedList<int> list2;

  list2 = list1;

  CHECK(list1.size() == 3);
  CHECK(list1.front() == 1);
  CHECK(list1.back() == 3);
  CHECK(list2.size() == 3);
  CHECK(list2.front() == 1);
  CHECK(list2.back() == 3);
}

