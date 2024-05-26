#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "../DoubleLinkedList.hpp"
#include "doctest.h"

TEST_CASE("push_back adds element to back of list") {
  DoubleLinkedList<std::string> list;
  list.push_back("hello");
  list.push_back("world");

  CHECK(list.size() == 2);
  CHECK(list.back() == "world");
}

TEST_CASE("push_back returns a reference to the list") {
  DoubleLinkedList<std::string> list1;
  DoubleLinkedList<std::string> list2;

  DoubleLinkedList<std::string>& list1Ref = list1.push_back("hello");
  DoubleLinkedList<std::string>& list2Ref = list2.push_back("world");

  CHECK(&list1Ref == &list1);
  CHECK(&list2Ref == &list2);
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

  list.push_back(std::move(obj1));
  list.push_back(std::move(obj2));
  list.push_back(std::move(obj3));

  CHECK(list.size() == 3);
  CHECK(list.back() == MyClass(3));
}

TEST_CASE("push_back can add rvalue elements") {
  DoubleLinkedList<std::string> list;
  list.push_back("hello");
  list.push_back(std::move(std::string("world")));

  CHECK(list.size() == 2);
  CHECK(list.back() == "world");
}
