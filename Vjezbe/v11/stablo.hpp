#pragma once

#include <iostream>

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
    ~Tree()
    {
      clear();
    }

    bool size() const
    {
      return size_;
    }

    bool empty() const
    {
      return root_ == nullptr;
    }

    template <typename F>
    void insert(F&& v)
    {
      auto new_node = new Node<T> { std::forward<F>(v) };
      if (empty())
      {
        root_ = new_node;
        size_++;
      }
      else
      {
        auto temp = root_;
        while (temp)
        {
          if (new_node->value < temp->value)
          {
            // idi lijevo
            if (temp->left_ == nullptr)
            {
              temp->left_ = new_node;
              size_++;
              return;
            }
            temp = temp->left_;
          }
          else
          {
            // veca ili jednaka - idi desno
            if (temp->right_ == nullptr)
            {
              temp->right_ = new_node;
              size_++;
              return;
            }
            temp = temp->right_;
          }
        }
      }
    }

    const T* find(const T& v) const
    {
      auto temp = root_;
      while (temp)
      {
        if (temp->value == v)
        {
          return &temp->value;
        }
        else if (temp->value < v)
        {
          temp = temp->right_;
        }
        else
        {
          temp = temp->left_;
        }
      }
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
      print_inorder(root_);
      std::cout << std::endl;
    }

    int depth() const
    {
      return depth(root_);
    }

    void preorder() const
    {
      if (!root_)
        return;
      print_preorder(root_);
      std::cout << std::endl;
    }
    void inorder() const
    {
      if (!root_)
        return;
      print_inorder(root_);
      std::cout << std::endl;
    }
    void postorder() const
    {
      if (!root_)
        return;
      print_postorder(root_);
      std::cout << std::endl;
    }

    void erase(const T& v)
    {
      Node<T>* previous = nullptr;
      auto current = root_;
      while (current != nullptr)
      {
        if (v > current->value)
        {
          previous = current;
          current = current->right_;
        }
        else if (v == current->value)
        {
          if (previous->left_->value == v)
            return eraseNode(previous->left_);
          else
            return eraseNode(previous->right_);
        }
        else
        {
          previous = current;
          current = current->left_;
        }
      }
    }

  private:
    static void print_preorder(const Node<T>* root)
    {
      std::cout << root->value << " ";
      if (root->left_)
        print_preorder(root->left_);
      if (root->right_)
        print_preorder(root->right_);
    }
    static void print_inorder(const Node<T>* root)
    {
      if (!root)
        return;
      print_inorder(root->left_);
      std::cout << root->value << ' ';
      print_inorder(root->right_);
    }
    static void print_postorder(const Node<T>* root)
    {
      if (root->left_)
        print_postorder(root->left_);
      if (root->right_)
        print_postorder(root->right_);
      std::cout << root->value << " ";
    }
    void eraseNode(Node<T>*& e)
    {
      if (e == nullptr)
      {
        return;
      }
      else if (e->left_ == nullptr && e->right_ == nullptr)
      {
        // cvor e nema dijece
        delete e;
        e = nullptr;
      }
      else if (e->right_ == nullptr)
      {
        // cvor e ima jedno dijete - left_
        auto temp = e;
        e = e->left_;
        delete temp;
      }
      else if (e->left_ == nullptr)
      {
        // cvor e ima jedno dijete - right_
        auto temp = e;
        e = e->right_;
        delete temp;
      }
      else
      {
        // cvor e ima dvoje dijece;
        Node<T>* previous = nullptr;
        auto current = e->left_;

        while (current->right_ != nullptr)
        {
          previous = current;
          current = current->right_;
        }

        e->value = current->value;

        if (previous != nullptr)
        {
          previous->right_ = current->left_;
        }
        else
        {
          e->left_ = current->left_;
        }

        delete current;
      }
      size_--;
    }

    static void clear_subtree(Node<T>* root)
    {
      if (!root)
        return;
      clear_subtree(root->left_);
      clear_subtree(root->right_);
      delete root;
    }

    static int depth(Node<T>* current)
    {
      if (current == nullptr) return -1;
      return 1 + std::max(depth(current->left_), depth(current->right_));
    }

    Node<T>* root_ = nullptr;
    size_t size_ = 0;
};
