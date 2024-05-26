#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "../DoubleLinkedList.hpp"
#include "doctest.h"

TEST_CASE("front returns reference to first element in list") {
  DoubleLinkedList<int> list;
  list.push_back(1);
  list.push_back(2);
  list.push_back(3);

  CHECK(list.front() == 1);

  list.front() = 4;

  CHECK(list.front() == 4);
}

TEST_CASE("front returns reference to first element of empty list") {
  DoubleLinkedList<int> list;

  CHECK_THROWS_AS(list.front(), std::out_of_range);
}

TEST_CASE("front can return reference to elements of different types") {
  DoubleLinkedList<int> intList;
  DoubleLinkedList<std::string> stringList;

  intList.push_back(1);
  stringList.push_back("hello");

  CHECK(intList.front() == 1);
  CHECK(stringList.front() == "hello");
}

TEST_CASE("front can return reference to elements of custom class type") {
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

  CHECK(list.front() == obj1);
}
