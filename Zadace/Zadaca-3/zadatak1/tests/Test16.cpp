#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "../DoubleLinkedList.hpp"
#include "doctest.h"

TEST_CASE("clear method removes all elements from list") {
  DoubleLinkedList<int> list;
  list.push_back(1);
  list.push_back(2);
  list.push_back(3);

  list.clear();

  CHECK(list.empty());
  CHECK(list.size() == 0);
  CHECK_THROWS_AS(list.front(), std::out_of_range);
  CHECK_THROWS_AS(list.back(), std::out_of_range);
}
