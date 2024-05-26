#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "../DoubleLinkedList.hpp"
#include "doctest.h"

TEST_CASE("push_front adds element to front of list") {
  DoubleLinkedList<std::string> list;
  list.push_front("world");
  list.push_front("hello");

  CHECK(list.size() == 2);
  CHECK(list.front() == "hello");
}

TEST_CASE("push_front returns a reference to the list") {
  DoubleLinkedList<std::string> list1;
  DoubleLinkedList<std::string> list2;

  DoubleLinkedList<std::string>& list1Ref = list1.push_front("hello");
  DoubleLinkedList<std::string>& list2Ref = list2.push_front("world");

  CHECK(&list1Ref == &list1);
  CHECK(&list2Ref == &list2);
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
}

TEST_CASE("push_front can add rvalue elements") {
  DoubleLinkedList<std::string> list;
  list.push_front(std::move(std::string("world")));
  list.push_front("hello");

  CHECK(list.size() == 2);
  CHECK(list.front() == "hello");
}
