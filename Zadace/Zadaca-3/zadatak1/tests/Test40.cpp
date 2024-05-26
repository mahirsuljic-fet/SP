#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "../DoubleLinkedList.hpp"
#include "doctest.h"
TEST_CASE("Test DoubleLinkedList erase") {
  DoubleLinkedList<int> list;
  list.push_back(1).push_back(2).push_back(3).push_back(4);

  SUBCASE("Erase single element") {
    auto pos = list.begin();
    ++pos;
    ++pos;
    auto it = list.erase(pos);
    CHECK(*it == 4);
    CHECK(list.size() == 3);
    CHECK(list.front() == 1);
    CHECK(list.back() == 4);
  }

  SUBCASE("Erase range of elements") {
    auto start = list.begin();
    ++start;
    auto end = list.begin();
    ++end;
    ++end;
    ++end;
    auto it = list.erase(start, end);
    CHECK(*it == 4);
    CHECK(list.size() == 2);
    CHECK(list.front() == 1);
    CHECK(list.back() == 4);
  }
}
