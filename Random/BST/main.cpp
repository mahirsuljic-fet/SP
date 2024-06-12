#include "BST.hpp"
#include <iostream>

int main()
{
  BST<int, std::string> bst;

  bst.insert(10, "Test10");
  bst.insert(15, "Test15");
  bst.insert(20, "Test20");
  bst.insert(12, "Test12");
  bst.insert(16, "Test16");
  bst.insert(18, "Test18");
  bst.insert(19, "Test19");

  bst.insert(5, "Test5");
  bst.insert(3, "Test3");
  bst.insert(8, "Test8");
  bst.insert(9, "Test9");
  bst.insert(4, "Test4");
  bst.insert(2, "Test2");
  bst.insert(1, "Test1");

  std::cout << bst << std::endl;

  int n = 15;
  std::cout << "ERASING -> " << n << std::endl;
  std::cout << (bst.erase(n) ? "(T)" : "(F)") << std::endl;
  std::cout << bst << std::endl;

  std::cout << bst.get(16) << std::endl;

  return 0;
}
