#pragma once

#include <cstddef>
#include <iostream>
#include <ostream>
#include <stdexcept>
#include <utility>

template <typename Key, typename Value>
class BST
{
  private:
    struct Node;

  public:
    BST();
    BST(const BST<Key, Value>&);
    BST(BST<Key, Value>&&);
    BST& operator=(const BST<Key, Value>&);
    BST& operator=(BST<Key, Value>&&);
    ~BST();

    template <typename Fwd_Key, typename Fwd_Value>
    bool insert(Fwd_Key&&, Fwd_Value&&);
    bool erase(const Key&);
    Value& get(const Key&);
    const Value& get(const Key&) const;
    bool exists(const Key&) const;
    size_t size() const { return size_; }
    void clear();

    template <typename K, typename V>
    friend std::ostream& operator<<(std::ostream&, const BST<K, V>&);

  private:
    Node* root_ = nullptr;
    size_t size_ = 0;

    static bool erase_node(Node*& node);
    static Node*& find_node(Node* root, const Key& key);
    static void print_tree(Node* root, std::ostream& out = std::cout);
    static void remove_tree(Node*& root);
    static Node* copy_tree(Node* root);
};

template <typename Key, typename Value>
struct BST<Key, Value>::Node
{
    Key key {};
    Value value {};
    Node* left = nullptr;
    Node* right = nullptr;
};

template <typename Key, typename Value>
BST<Key, Value>::BST()
  : root_ { nullptr }, size_ { 0 } { }

template <typename Key, typename Value>
BST<Key, Value>::BST(const BST<Key, Value>& other)
{
  this->root_ = copy_tree(other.root_);
  this->size_ = other.size_;
}

template <typename Key, typename Value>
BST<Key, Value>::BST(BST<Key, Value>&& other)
{
  this->root_ = other.root_;
  this->size_ = other.size_;
  other.root_ = nullptr;
  other.size_ = 0;
}

template <typename Key, typename Value>
BST<Key, Value>& BST<Key, Value>::operator=(const BST<Key, Value>& other)
{
  if (this != &other)
  {
    this->root_ = copy_tree(other.root_);
    this->size_ = other.size_;
  }
  return *this;
}

template <typename Key, typename Value>
BST<Key, Value>& BST<Key, Value>::operator=(BST<Key, Value>&& other)
{
  if (this != &other)
  {
    this->root_ = other.root_;
    this->size_ = other.size_;
    other.root_ = nullptr;
    other.size_ = 0;
  }
  return *this;
}

template <typename Key, typename Value>
BST<Key, Value>::~BST()
{
  clear();
}

template <typename Key, typename Value>
template <typename Fwd_Key, typename Fwd_Value>
bool BST<Key, Value>::insert(Fwd_Key&& key, Fwd_Value&& value)
{
  if (root_ == nullptr)
  {
    root_ = new Node { key, value };
    return true;
  }

  Node*& new_node = find_node(root_, key);

  if (new_node != nullptr)
    return false;

  new_node = new Node { std::forward<Fwd_Key>(key), std::forward<Fwd_Value>(value) };

  return true;
}

template <typename Key, typename Value>
bool BST<Key, Value>::erase(const Key& key)
{
  return erase_node(find_node(root_, key));
}

template <typename Key, typename Value>
Value& BST<Key, Value>::get(const Key& key)
{
  Node*& node = find_node(root_, key);
  if (node == nullptr)
    throw std::runtime_error("Element sa datim kljucem ne postoji");
  return node->value;
}

template <typename Key, typename Value>
const Value& BST<Key, Value>::get(const Key& key) const
{
  const Node*& node = find_node(root_, key);
  if (node == nullptr)
    throw std::runtime_error("Element sa datim kljucem ne postoji");
  return node->value;
}

template <typename Key, typename Value>
void BST<Key, Value>::clear()
{
  remove_tree(root_);
  size_ = 0;
}

template <typename Key, typename Value>
bool BST<Key, Value>::exists(const Key& key) const
{
  return find_node(root_, key) != nullptr;
}

template <typename Key, typename Value>
std::ostream& operator<<(std::ostream& out, const BST<Key, Value>& tree)
{
  BST<Key, Value>::print_tree(tree.root_, out);
  return out;
}

template <typename Key, typename Value>
bool BST<Key, Value>::erase_node(Node*& node)
{
  if (node == nullptr) return false;

  if (node->left == nullptr)
  {
    // NO LEFT CHILD
    if (node->right == nullptr)
    {
      // NO CHILDREN
      delete node;
      node = nullptr;
      return true;
    }
    else
    {
      // ONLY RIGHT CHILD
      Node* temp = node;
      node = node->right;
      delete temp;
      return true;
    }
  }
  else
  {
    // HAS LEFT CHILD
    if (node->right == nullptr)
    {
      // ONLY LEFT CHILD
      Node* temp = node;
      node = node->left;
      delete temp;
      return true;
    }
    else
    {
      // BOTH CHILDREN
      Node* previous = node;
      Node* current = node->right;
      while (current->left != nullptr)
      {
        previous = current;
        current = current->left;
      }
      std::swap(current->key, node->key);
      std::swap(current->value, node->value);
      erase_node(previous == node ? previous->right : previous->left);
      return true;
    }
  }

  return false;
}

template <typename Key, typename Value>
typename BST<Key, Value>::Node*& BST<Key, Value>::find_node(Node* root, const Key& key)
{
  Node* current = root;
  Node* previous = nullptr;
  bool last_direction = false; // false - left ; true - right

  while (current != nullptr)
  {
    if (key == current->key) break;

    previous = current;

    if (key < current->key)
    {
      current = current->left;
      last_direction = false;
    }
    else
    {
      current = current->right;
      last_direction = true;
    }
  }

  if (last_direction)
    return previous->right;
  else
    return previous->left;
}

template <typename Key, typename Value>
void BST<Key, Value>::print_tree(Node* root, std::ostream& out)
{
  if (root == nullptr) return;

  print_tree(root->left, out);
  out << "{" << root->key << ", " << root->value << "} ";
  print_tree(root->right, out);
}

template <typename Key, typename Value>
void BST<Key, Value>::remove_tree(Node*& root)
{
  if (root == nullptr) return;
  remove_tree(root->left);
  remove_tree(root->right);
  delete root;
  root = nullptr;
}

template <typename Key, typename Value>
typename BST<Key, Value>::Node* BST<Key, Value>::copy_tree(Node* root)
{
  if (root == nullptr) return nullptr;
  Node* copy = new Node { root->key, root->value };
  copy->left = copy_tree(root->left);
  copy->right = copy_tree(root->right);
  return copy;
}
