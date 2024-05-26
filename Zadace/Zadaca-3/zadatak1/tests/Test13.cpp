#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "../DoubleLinkedList.hpp"
#include "doctest.h"

TEST_CASE("move constructor moves elements from source list") {
  DoubleLinkedList<int> list1;
  list1.push_back(1);
  list1.push_back(2);
  list1.push_back(3);

  DoubleLinkedList<int> list2(std::move(list1));

  CHECK(list1.empty());
  CHECK(list2.size() == 3);
  CHECK(list2.front() == 1);
  CHECK(list2.back() == 3);
  CHECK(list1.size() == 0);
  CHECK_THROWS_AS(list1.front(), std::out_of_range);
  CHECK_THROWS_AS(list1.back(), std::out_of_range);
}

TEST_CASE("move constructor creates new list with independent memory") {
  DoubleLinkedList<int> list1;
  list1.push_back(1);
  list1.push_back(2);
  list1.push_back(3);

  DoubleLinkedList<int> list2(std::move(list1));

  CHECK(list2.size() == 3);
  CHECK(list2.front() == 1);
  CHECK(list2.back() == 3);
  CHECK(list1.size() == 0);
  CHECK_THROWS_AS(list1.front(), std::out_of_range);
  CHECK_THROWS_AS(list1.back(), std::out_of_range);
}
