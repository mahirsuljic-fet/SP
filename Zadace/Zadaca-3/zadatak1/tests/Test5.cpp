#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "../DoubleLinkedList.hpp"
#include "doctest.h"

TEST_CASE("destructor deletes all nodes in list") {
  DoubleLinkedList<int>* list = new DoubleLinkedList<int>();
  list->push_back(1);
  list->push_back(2);
  list->push_back(3);

  CHECK(list->size() == 3);

  delete list;

  CHECK(list->size() == 0);
}

TEST_CASE("destructor does not delete null pointer") {
  DoubleLinkedList<int>* list = nullptr;

  CHECK_NOTHROW(delete list);
}
