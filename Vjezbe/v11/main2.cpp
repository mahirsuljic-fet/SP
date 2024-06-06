#include "stablo.hpp"
#include <iostream>

int main()
{
  Tree<int> moj_tree;

  moj_tree.insert(5);
  moj_tree.insert(1);
  moj_tree.insert(2);
  moj_tree.insert(3);
  moj_tree.insert(10);
  moj_tree.insert(11);
  moj_tree.insert(12);

  std::cout << "Testiramo copy ctor" << std::endl;
  auto moj_tree1 = moj_tree;
  std::cout << "mojtree ";
  moj_tree.print();
  std::cout << "mojtree1 ";
  moj_tree1.print();

  std::cout << "Testiramo move ctor" << std::endl;
  auto moj_tree2 = std::move(moj_tree);
  std::cout << "mojtree2 ";
  moj_tree2.print();

  std::cout << "Testiramo copy=" << std::endl;
  moj_tree = moj_tree1;
  std::cout << "mojtree ";
  moj_tree.print();

  std::cout << "Testiramo move=" << std::endl;
  std::cout << "mojtree ";
  moj_tree = std::move(moj_tree1);
  std::cout << "Print" << std::endl;
  moj_tree.print();

  return 0;
}
