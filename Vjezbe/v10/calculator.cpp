#include <iostream>

// 3 * 7 + 8
// 3 * 7 + 8 - 10

//          -
//        /   \
//       +     10
//     /   \
//    *     8
//   / \
//  3   7

struct Node
{
    virtual int eval() = 0;
    virtual ~Node() { }
};

// 3, 7, 8
struct NumberNode : public Node
{
    NumberNode(int b) : broj { b } { }
    ~NumberNode() { }
    int eval() override { return broj; }
    int broj;
};

// +, *, /, -
struct OpNode : public Node
{
    OpNode(char o, Node* left, Node* right) : op { o }, left_ { left }, right_ { right } { }
    ~OpNode()
    {
      delete left_;
      delete right_;
    }

    int eval() override
    {
      switch (op)
      {
      case '+':
        return left_->eval() + right_->eval();
      case '-':
        return left_->eval() - right_->eval();
      case '*':
        return left_->eval() * right_->eval();
      case '/':
        return left_->eval() / right_->eval();
      }
      throw std::string { "Undefined" };
    }

    char op;
    Node* left_;
    Node* right_;
};

int main()
{
  // (3 + 7) * 8
  Node* n1 = new NumberNode { 3 };
  Node* n2 = new NumberNode { 7 };

  n1 = new OpNode('+', n1, n2);
  n2 = new NumberNode { 8 };

  n1 = new OpNode('*', n1, n2);

  std::cout << n1->eval() << std::endl;

  delete n1;

  return 0;
}
