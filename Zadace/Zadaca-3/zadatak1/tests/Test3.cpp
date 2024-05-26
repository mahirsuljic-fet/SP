#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN

#include "../DoubleLinkedList.hpp"
#include "doctest.h"

TEST_CASE("push_back adds element to empty list") {
  DoubleLinkedList<int> list;
  list.push_back(1);

  CHECK(list.size() == 1);
  CHECK(list.front() == 1);
  CHECK(list.back() == 1);
}

TEST_CASE("push_back can add elements of different types") {
  DoubleLinkedList<int> intList;
  DoubleLinkedList<std::string> stringList;

  intList.push_back(1);
  stringList.push_back("hello");

  CHECK(intList.size() == 1);
  CHECK(stringList.size() == 1);
  CHECK(intList.back() == 1);
  CHECK(stringList.back() == "hello");
}

TEST_CASE("push_back can add elements of custom class type") {
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

  list.push_back(obj1);
  list.push_back(obj2);
  list.push_back(obj3);

  CHECK(list.size() == 3);
  CHECK(list.back() == obj3);
}
