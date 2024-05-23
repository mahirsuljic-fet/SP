#include "stablo.hpp"

#include <iostream>
#include <string>

int main()
{
  Tree<int> moj_tree;

  moj_tree.insert(5);
  moj_tree.print();

  moj_tree.insert(1);
  moj_tree.print();

  moj_tree.insert(2);
  moj_tree.print();

  moj_tree.insert(3);
  moj_tree.print();

  moj_tree.insert(10);
  moj_tree.print();

  moj_tree.insert(11);
  moj_tree.print();

  moj_tree.insert(12);
  moj_tree.print();

  auto it = moj_tree.find(3);
  if (it)
    std::cout << "Pronasli smo element " << *it << std::endl;
  else
    std::cout << "Nismo pronasli element" << std::endl;

  it = moj_tree.find(12);
  if (it)
    std::cout << "Pronasli smo element " << *it << std::endl;
  else
    std::cout << "Nismo pronasli element" << std::endl;

  it = moj_tree.find(16);
  if (it)
    std::cout << "Pronasli smo element " << *it << std::endl;
  else
    std::cout << "Nismo pronasli element" << std::endl;

  return 0;
}
