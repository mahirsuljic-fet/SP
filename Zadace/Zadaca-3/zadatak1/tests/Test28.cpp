#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "../DoubleLinkedList.hpp"
#include "doctest.h"

TEST_CASE("Iterator arrow operator") {
  struct Data {
    int a = 20;
    int b = 30;
    char x = 'x';
    Data() = default;
    Data(int a1, int b1, char x1) : a{a1}, b{b1}, x{x1} {}
  };
  DoubleLinkedList<Data> list;
  list.push_back(Data{});
  list.push_back(Data{50, 70, 'a'});
  list.push_back(Data{-4, -2, 'A'});

  // Test arrow operator
  auto it = list.begin();
  CHECK(it->a == 20);
  CHECK(it->b == 30);
  CHECK(it->x == 'x');

  // Test arrow operator with const iterator
  const auto& constList = list;
  auto cit = constList.begin();
  CHECK(cit->a == 20);
  CHECK(cit->b == 30);
  CHECK(cit->x == 'x');
}
