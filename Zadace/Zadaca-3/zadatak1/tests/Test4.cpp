#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "doctest.h"
#include "../DoubleLinkedList.hpp"

TEST_CASE("push_front adds element to front of list") {
  DoubleLinkedList<int> list;
  list.push_front(1);
  list.push_front(2);
  list.push_front(3);

  CHECK(list.size() == 3);
  CHECK(list.front() == 3);
}

TEST_CASE("push_front returns a reference to the list") {
  DoubleLinkedList<int> list1;
  DoubleLinkedList<int> list2;

  DoubleLinkedList<int>& list1Ref = list1.push_front(1);
  DoubleLinkedList<int>& list2Ref = list2.push_front(2);

  CHECK(&list1Ref == &list1);
  CHECK(&list2Ref == &list2);
}

TEST_CASE("push_front adds element to empty list") {
  DoubleLinkedList<int> list;
  list.push_front(1);

  CHECK(list.size() == 1);
  CHECK(list.front() == 1);
  CHECK(list.back() == 1);
}

TEST_CASE("push_front can add elements of different types") {
  DoubleLinkedList<int> intList;
  DoubleLinkedList<std::string> stringList;

  intList.push_front(1);
  stringList.push_front("hello");

  CHECK(intList.size() == 1);
  CHECK(stringList.size() == 1);
  CHECK(intList.front() == 1);
  CHECK(stringList.front() == "hello");
}

TEST_CASE("push_front can add elements of custom class type") {
  class MyClass {
    public:
      int value;

      MyClass(int value) : value(value) {}
      bool operator==(const MyClass& other) const {
        return value == other.value;
      }
  };

  DoubleLinkedList<MyClass> list;
  MyClass obj1(1);
  MyClass obj2(2);
  MyClass obj3(3);

  list.push_front(obj1);
  list.push_front(obj2);
  list.push_front(obj3);

  CHECK(list.size() == 3);
  CHECK(list.front() == obj3);
}

