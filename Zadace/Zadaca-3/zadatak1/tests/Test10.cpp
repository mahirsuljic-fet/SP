#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "../DoubleLinkedList.hpp"
#include "doctest.h"

TEST_CASE("pop_front removes first element from list") {
  DoubleLinkedList<int> list;
  list.push_front(2);
  list.push_front(1);
  list.push_front(0);

  CHECK(list.size() == 3);
  CHECK(list.front() == 0);

  list.pop_front();

  CHECK(list.size() == 2);
  CHECK(list.front() == 1);

  list.pop_front();

  CHECK(list.size() == 1);
  CHECK(list.front() == 2);

  list.pop_front();

  CHECK(list.size() == 0);
  CHECK_THROWS_AS(list.front(), std::out_of_range);
}

TEST_CASE("pop_front returns a reference to the list") {
  DoubleLinkedList<int> list1;
  DoubleLinkedList<int> list2;

  DoubleLinkedList<int>& list1Ref = list1.push_front(1).pop_front();
  DoubleLinkedList<int>& list2Ref = list2.push_front(2).pop_front();

  CHECK(&list1Ref == &list1);
  CHECK(&list2Ref == &list2);
}

TEST_CASE("pop_front on empty list throws exception") {
  DoubleLinkedList<int> list;

  CHECK_THROWS_AS(list.pop_front(), std::out_of_range);
}

TEST_CASE("pop_front can remove elements of custom class type") {
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

  list.push_front(std::move(obj1));
  list.push_front(std::move(obj2));
  list.push_front(std::move(obj3));

  CHECK(list.size() == 3);
  CHECK(list.front() == MyClass(3));

  list.pop_front();

  CHECK(list.size() == 2);
  CHECK(list.front() == MyClass(2));
}
