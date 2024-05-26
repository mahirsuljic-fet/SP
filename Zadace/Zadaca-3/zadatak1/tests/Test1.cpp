#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "../DoubleLinkedList.hpp"
#include "doctest.h"

TEST_CASE("Testing Node constructor") {
  SUBCASE("Creating node for integer type") {
    int value = 10;
    Node<int> node(value);
    CHECK(node.data == value);
    CHECK(node.next == nullptr);
    CHECK(node.prev == nullptr);
  }

  SUBCASE("Creating node for string type") {
    std::string value = "testing";
    Node<std::string> node(value);
    CHECK(node.data == value);
    CHECK(node.next == nullptr);
    CHECK(node.prev == nullptr);
  }

  SUBCASE("Creating node for my structure type") {
    struct Vjezbe {
      std::string predmet;
    };
    Vjezbe v{"SP"};
    Node<Vjezbe> node(v);
    CHECK(node.data.predmet == v.predmet);
    CHECK(node.next == nullptr);
    CHECK(node.prev == nullptr);
  }
}
