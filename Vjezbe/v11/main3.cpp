#include "stablo.hpp"

#include <iostream>

int main() {
  Tree<int> moj_tree;

  moj_tree.insert(5);
  moj_tree.insert(1);
  moj_tree.insert(2);
  moj_tree.insert(3);
  moj_tree.insert(10);
  moj_tree.insert(11);
  moj_tree.insert(12);

  std::cout << "Dubina: " << moj_tree.depth() << std::endl;

  moj_tree.preorder();
  std::cout << '\n';
  moj_tree.inorder();
  std::cout << "\n";
  moj_tree.postorder();
  std::cout << std::endl;

  // moj_tree.clear();
  // moj_tree.print();

  moj_tree.erase(10);
  moj_tree.print();

  moj_tree.erase(30);
  moj_tree.print();

  moj_tree.erase(5);
  moj_tree.print();

  moj_tree.erase(3);
  moj_tree.print();

  moj_tree.erase(2);
  moj_tree.print();

  moj_tree.erase(1);
  moj_tree.erase(11);
  moj_tree.erase(12);
  moj_tree.print();

  return 0;
}
