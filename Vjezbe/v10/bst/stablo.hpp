#pragma once

#include <iostream>
#include <queue>
#include <utility>

template <typename T>
struct Node
{
    T value;
    Node* left_ = nullptr;
    Node* right_ = nullptr;
};

template <typename T>
class Tree
{
  public:
    Tree() = default;
    Tree(const Tree& other) = delete;
    Tree(Tree&& other) = default;
    Tree& operator=(const Tree& other) = delete;
    Tree& operator=(Tree&& other) = default;
    ~Tree() { clear(); }

    bool size() const { return size_; }
    bool empty() const { return root_ == nullptr; }

    template <typename F>
    void insert(F&& v)
    {
      auto new_node = new Node<T> { std::forward<F>(v) };
      ++size_;

      if (root_ == nullptr)
      {
        root_ = new_node;
        return;
      }

      auto temp = root_;
      while (temp)
      {
        if (temp->left_ == nullptr)
        {
          temp->left_ = new_node;
          return;
        }

        if (temp->right_ == nullptr)
        {
          temp->right_ = new_node;
          return;
        }

        if (new_node->value < temp->value)
          temp = temp->left_;
        else
          temp = temp->right_;
      }
    }

    const T* find(const T& v) const
    {
      return nullptr;
    }

    void clear()
    {
      clear_subtree(root_);
      size_ = 0;
      root_ = nullptr;
    }

    void print() const
    {
      print_subtree(root_);
      std::cout << std::endl;
    }

  private:
    static void print_subtree(const Node<T>* root)
    {
      if (root == nullptr) return;
      std::cout << root->value << " ";
      print_subtree(root->left_);
      print_subtree(root->right_);
    }

    static void clear_subtree(Node<T>* root)
    {
      if (root == nullptr) return;
      clear_subtree(root->left_);
      clear_subtree(root->right_);
      delete root;
    }

    Node<T>* root_ = nullptr;
    size_t size_ = 0;
};
