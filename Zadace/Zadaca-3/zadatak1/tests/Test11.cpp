#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "../DoubleLinkedList.hpp"
#include "doctest.h"

TEST_CASE("pop_back removes last element from list") {
  DoubleLinkedList<int> list;
  list.push_back(0);
  list.push_back(1);
  list.push_back(2);

  CHECK(list.size() == 3);
  CHECK(list.back() == 2);

  list.pop_back();

  CHECK(list.size() == 2);
  CHECK(list.back() == 1);

  list.pop_back();

  CHECK(list.size() == 1);
  CHECK(list.back() == 0);

  list.pop_back();

  CHECK(list.size() == 0);
  CHECK_THROWS_AS(list.back(), std::out_of_range);
}

TEST_CASE("pop_back returns a reference to the list") {
  DoubleLinkedList<int> list1;
  DoubleLinkedList<int> list2;

  DoubleLinkedList<int>& list1Ref = list1.push_back(1).pop_back();
  DoubleLinkedList<int>& list2Ref = list2.push_back(2).pop_back();

  CHECK(&list1Ref == &list1);
  CHECK(&list2Ref == &list2);
}

TEST_CASE("pop_back on empty list throws exception") {
  DoubleLinkedList<int> list;

  CHECK_THROWS_AS(list.pop_back(), std::out_of_range);
}

TEST_CASE("pop_back can remove elements of custom class type") {
  class MyClass {
public:
    int value;

    MyClass(int value) : value(value) {}
    bool operator==(const MyClass& other) const { return value == other.value; }
  };

  DoubleLinkedList<MyClass> list;
  MyClass obj1(1);
  MyClass obj2(2);
  MyClass obj3(3);

  list.push_back(std::move(obj1));
  list.push_back(std::move(obj2));
  list.push_back(std::move(obj3));

  CHECK(list.size() == 3);
  CHECK(list.back() == MyClass(3));

  list.pop_back();

  CHECK(list.size() == 2);
  CHECK(list.back() == MyClass(2));
}
