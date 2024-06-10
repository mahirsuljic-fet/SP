#pragma once

#include <cstddef>
#include <iostream>
#include <ostream>
#include <stdexcept>
#include <utility>

template <typename K, typename V>
class Map
{
  public:
    Map();
    Map(const Map&);
    Map(Map&&);
    Map& operator=(const Map&);
    Map& operator=(Map&&);
    ~Map();
    bool empty() const { return size_ == 0; }
    size_t size() const { return size_; }
    V& at(const K&);
    const V& at(const K&) const;
    V* find(const K&);
    const V* find(const K&) const;
    V& operator[](const K&);
    template <typename F>
    V& insert(const K&, F&&);
    bool erase(const K&);
    void clear();
    std::ostream& print(std::ostream& out = std::cout) const;

  private:
    struct Node;
    Node* root_ = nullptr;
    size_t size_ = 0;
    static Node* node_copy(Node*);
    static Node* find_node(Node*, K);
    static void delete_node(Node*);
    static void erase_node(Node*&);
    static std::ostream& print_impl(Node* node, std::ostream& out = std::cout);
};

template <typename K, typename V>
struct Map<K, V>::Node
{
    K key {};
    V value {};
    Node* left = nullptr;
    Node* right = nullptr;
};

template <typename K, typename V>
Map<K, V>::Map()
  : root_ { nullptr }, size_ { 0 } { }

template <typename K, typename V>
Map<K, V>::Map(const Map& other)
  : root_ { node_copy(other.root_) }, size_ { other.size_ } { }

template <typename K, typename V>
Map<K, V>::Map(Map&& other)
  : root_ { other.root_ }, size_ { other.size_ }
{
  other.root_ = nullptr;
  other.size_ = 0;
}

template <typename K, typename V>
Map<K, V>& Map<K, V>::operator=(const Map& other)
{
  if (this != &other)
  {
    this->size_ = other.size_;
    this->root_ = node_copy(other.root_);
  }
  return *this;
}

template <typename K, typename V>
Map<K, V>& Map<K, V>::operator=(Map&& other)
{
  if (this != &other)
  {
    this->size_ = other.size_;
    this->root_ = other.root_;
    other.root_ = nullptr;
    other.size_ = 0;
  }
  return *this;
}

template <typename K, typename V>
Map<K, V>::~Map()
{
  clear();
}

template <typename K, typename V>
V& Map<K, V>::at(const K& key)
{
  Node* node = find_node(root_, key);
  if (node == nullptr) throw std::invalid_argument("Element sa datim kljucem ne postoji");
  return node->value;
}

template <typename K, typename V>
const V& Map<K, V>::at(const K& key) const
{
  Node* node = find_node(root_, key);
  if (node == nullptr) throw std::invalid_argument("Element sa datim kljucem ne postoji");
  return node->value;
}

template <typename K, typename V>
V* Map<K, V>::find(const K& key)
{
  Node* node = find_node(root_, key);
  if (node == nullptr) return nullptr;
  return &node->value;
}

template <typename K, typename V>
const V* Map<K, V>::find(const K& key) const
{
  Node* node = find_node(root_, key);
  if (node == nullptr) return nullptr;
  return &node->value;
}

template <typename K, typename V>
V& Map<K, V>::operator[](const K& key)
{
  Node* current = root_;
  Node* previous = nullptr;

  while (current != nullptr)
  {
    if (current->key == key)
      return current->value;

    previous = current;

    if (key < current->key)
      current = current->left;
    else // if (key > current->key)
      current = current->right;
  }

  Node* new_node = new Node { key };

  if (root_ != nullptr)
  {
    if (previous == nullptr)
      previous = root_;

    if (key < previous->key)
      previous->left = new_node;
    else // if(key > previous->key)
      previous->right = new_node;
  }
  else
    root_ = new_node;

  ++size_;

  return new_node->value;
}

template <typename K, typename V>
template <typename F>
V& Map<K, V>::insert(const K& key, F&& value)
{
  Node* current = root_;
  Node* previous = nullptr;

  while (current != nullptr)
  {
    if (current->key == key)
      throw std::invalid_argument("Element sa navedenim kljucem vec postoji");

    previous = current;

    if (key < current->key)
      current = current->left;
    else // if (key > current->key)
      current = current->right;
  }

  Node* new_node = new Node { key, std::forward<F>(value) };

  if (root_ != nullptr)
  {
    if (previous == nullptr)
      previous = root_;

    if (key < previous->key)
      previous->left = new_node;
    else // if(key > previous->key)
      previous->right = new_node;
  }
  else
    root_ = new_node;

  ++size_;

  return new_node->value;
}

template <typename K, typename V>
bool Map<K, V>::erase(const K& key)
{
  if (this->empty()) return false;

  Node* current = root_;
  Node* previous = nullptr;

  if (root_->key == key)
  {
    erase_node(root_);
    return true;
  }

  while (current != nullptr)
  {
    if (current->key == key)
    {
      if (previous->left != nullptr)
      {
        if (previous->left->key == key)
        {
          erase_node(previous->left);
          return true;
        }
      }
      erase_node(previous->right);
      return true;
    }
    else if (key > current->key)
    {
      previous = current;
      current = current->right;
    }
    else
    {
      previous = current;
      current = current->left;
    }
  }

  return false;
}

template <typename K, typename V>
void Map<K, V>::clear()
{
  delete_node(root_);
  root_ = nullptr;
  size_ = 0;
}

template <typename K, typename V>
typename Map<K, V>::Node* Map<K, V>::node_copy(Node* node)
{
  if (node == nullptr) return nullptr;
  return new Node { node->key, node->value, node_copy(node->left), node_copy(node->right) };
}

template <typename K, typename V>
typename Map<K, V>::Node* Map<K, V>::find_node(Node* node, K key)
{
  if (node == nullptr) return nullptr;
  if (node->key == key) return node;

  Node* result = find_node(node->left, key);
  if (result == nullptr)
    return find_node(node->right, key);

  return result;
}

template <typename K, typename V>
void Map<K, V>::delete_node(Node* node)
{
  if (node == nullptr) return;
  delete_node(node->left);
  delete_node(node->right);
  delete node;
}

template <typename K, typename V>
void Map<K, V>::erase_node(Node*& node)
{
  if (node->left == nullptr)
  {
    if (node->right == nullptr)
    {
      Node* temp = node;
      node = nullptr;
      delete temp;
      return;
    }
    else
    {
      Node* temp = node;
      node = node->right;
      delete temp;
      return;
    }
  }
  else
  {
    if (node->right == nullptr)
    {
      Node* temp = node;
      node = node->left;
      delete temp;
      return;
    }
    else
    {
      Node* current = node->right;
      Node* previous = node;

      while (current->left != nullptr)
      {
        previous = current;
        current = current->left;
      }

      std::swap(current->key, node->key);
      std::swap(current->value, node->value);

      if (previous->left != nullptr)
      {
        if (previous->left->key == current->key)
        {
          erase_node(previous->left);
          return;
        }
      }

      erase_node(previous->right);
    }
  }
}

template <typename K, typename V>
std::ostream& Map<K, V>::print(std::ostream& out) const
{
  print_impl(root_);
  out << std::endl;
  return out;
}

template <typename K, typename V>
std::ostream& Map<K, V>::print_impl(Node* node, std::ostream& out)
{
  if (node == nullptr) return out;
  print_impl(node->left);
  out << node->value << " ";
  print_impl(node->right);
  return out;
}
