#include <iostream>
#include <string>
#include <vector>

// /home/user/
// |-Documents/
// |-Downloads/
// | |-ubuntu.iso
// |-FET/
// | |-main.cpp
// | |-provjere/
// | | |-provjera1.cpp
// | | |-provjera2.cpp

struct Node
{
    std::string name;
    std::vector<Node*> children;
};

void print_tree(const Node* root, int depth)
{
  std::cout << std::string(2 * depth, ' ') << root->name << std::endl;
  for (const auto& child : root->children)
    print_tree(child, depth + 1);
}

void delete_tree(const Node* root)
{
  for (const auto& child : root->children)
    delete_tree(child);
  delete root;
}

int main()
{
  auto root = new Node();
  root->name = "/home/user/";

  auto n1 = new Node();
  n1->name = "Downloads";

  root->children.push_back(n1);

  n1 = new Node();
  n1->name = "Documents";
  root->children.push_back(n1);

  n1 = new Node();
  n1->name = "FET";

  auto n2 = new Node();
  n2->name = "OOP";
  n1->children.push_back(n2);

  n2 = new Node();
  n2->name = "SP";
  n1->children.push_back(n2);

  n2 = new Node();
  n2->name = "URA";
  n1->children.push_back(n2);

  root->children.push_back(n1);

  print_tree(root, 0);
  delete_tree(root);

  return 0;
};
