#pragma once

#include <algorithm>
#include <cstddef>
#include <functional>
#include <future>
#include <iterator>
#include <stdexcept>

template <typename T>
struct Node
{
    Node* prev { nullptr };
    Node* next { nullptr };
    T data;
    Node(const T& element) : data { element }, next { nullptr }, prev { nullptr } { }
};

template <typename T>
class DoubleLinkedList
{
  public:
    class Iterator;
    using ReverseIterator = std::reverse_iterator<Iterator>;

    DoubleLinkedList();
    DoubleLinkedList(const DoubleLinkedList&);
    DoubleLinkedList(DoubleLinkedList&&);
    DoubleLinkedList& operator=(const DoubleLinkedList&);
    DoubleLinkedList& operator=(DoubleLinkedList&&);
    ~DoubleLinkedList();

    DoubleLinkedList& push_back(const T&);
    DoubleLinkedList& push_front(const T&);
    DoubleLinkedList& push_back(T&&);
    DoubleLinkedList& push_front(T&&);
    DoubleLinkedList& pop_front();
    DoubleLinkedList& pop_back();
    bool empty() const { return !size_; }
    size_t size() const { return size_; }
    T& front();
    const T& front() const;
    T& back();
    const T& back() const;
    Iterator begin() const { return Iterator { head_ }; }
    Iterator end() const { return Iterator { nullptr }; }
    const Iterator cbegin() const { return Iterator { head_ }; }
    const Iterator cend() const { return Iterator { nullptr }; }
    Iterator rbegin() const { return Iterator { tail_ }; }
    Iterator rend() const { return Iterator { nullptr }; }
    const Iterator rcbegin() const { return Iterator { tail_ }; }
    const Iterator rcend() const { return Iterator { nullptr }; }
    void clear();
    Iterator insert(Iterator pos, const T& element);
    Iterator erase(Iterator pos);
    Iterator erase(Iterator beginIt, Iterator endIt);
    void remove_if(std::function<bool(const T&)>&& p);
    void reverse();
    Iterator find(const T& element) const;

  private:
    void dealoc();
    Node<T>* head_ { nullptr };
    Node<T>* tail_ { nullptr };
    size_t size_ { 0 };
};

template <typename T>
class DoubleLinkedList<T>::Iterator
{
  public:
    using iterator_category = std::bidirectional_iterator_tag;
    using value_type = T;
    using pointer = T*;
    using reference = T&;
    using difference_type = ptrdiff_t;

    friend class DoubleLinkedList<T>;

    Iterator() : node_ { nullptr } { }
    Iterator(Node<T>* node) : node_ { node } { }
    Iterator(const Iterator&);
    Iterator(Iterator&&);
    Iterator& operator=(const Iterator&);
    Iterator& operator=(Iterator&&);

    reference operator*() { return node_->data; }
    reference operator*() const { return node_->data; }
    pointer operator->() { return &node_->data; }
    pointer operator->() const { return &node_->data; }
    Iterator& operator++();
    Iterator operator++(int);
    Iterator& operator--();
    Iterator operator--(int);
    bool operator==(Iterator other) { return this->node_ == other.node_; }
    bool operator==(Iterator other) const { return this->node_ == other.node_; }
    bool operator!=(Iterator other) { return this->node_ != other.node_; }
    bool operator!=(Iterator other) const { return this->node_ != other.node_; }

    Node<T>* node() { return node_; }
    const Node<T>* node() const { return node_; }

  private:
    Node<T>* node_ { nullptr };
};

template <typename T>
DoubleLinkedList<T>::DoubleLinkedList() : head_(nullptr), tail_(nullptr), size_(0) { }

template <typename T>
DoubleLinkedList<T>::DoubleLinkedList(const DoubleLinkedList& other)
{
  for (auto it_other = other.begin(); it_other != other.end(); ++it_other)
    this->push_back(*it_other);
}

template <typename T>
DoubleLinkedList<T>::DoubleLinkedList(DoubleLinkedList&& other)
{
  for (auto it_other = other.begin(); it_other != other.end(); ++it_other)
    this->push_back(std::move(*it_other));
  other.size_ = 0;
}

template <typename T>
DoubleLinkedList<T>& DoubleLinkedList<T>::operator=(const DoubleLinkedList& other)
{
  if (this != &other)
  {
    this->clear();
    for (auto it_other = other.begin(); it_other != other.end(); ++it_other)
      this->push_back(*it_other);
  }
  return *this;
}

template <typename T>
DoubleLinkedList<T>& DoubleLinkedList<T>::operator=(DoubleLinkedList&& other)
{
  if (this != &other)
  {
    this->clear();
    for (auto it_other = other.begin(); it_other != other.end(); ++it_other)
      this->push_back(std::move(*it_other));
    other.size_ = 0;
  }
  return *this;
}

template <typename T>
DoubleLinkedList<T>::~DoubleLinkedList()
{
  this->clear();
}

template <typename T>
DoubleLinkedList<T>& DoubleLinkedList<T>::push_back(const T& value)
{
  Node<T>* new_node = new Node<T> { value };
  new_node->prev = tail_;

  if (!this->empty())
  {
    tail_->next = new_node;
    tail_ = new_node;
  }
  else
    *(tail_ = head_ = new_node);

  ++size_;

  return *this;
}

template <typename T>
DoubleLinkedList<T>& DoubleLinkedList<T>::push_front(const T& value)
{
  Node<T>* new_node = new Node<T> { value };
  new_node->next = head_;

  if (!this->empty())
  {
    head_->prev = new_node;
    head_ = new_node;
  }
  else
    *(head_ = tail_ = new_node);

  ++size_;

  return *this;
}

template <typename T>
DoubleLinkedList<T>& DoubleLinkedList<T>::push_back(T&& value)
{
  Node<T>* new_node = new Node<T> { std::move(value) };
  new_node->prev = tail_;

  if (!this->empty())
  {
    tail_->next = new_node;
    tail_ = new_node;
  }
  else
    *(tail_ = head_ = new_node);

  ++size_;

  return *this;
}

template <typename T>
DoubleLinkedList<T>& DoubleLinkedList<T>::push_front(T&& value)
{
  Node<T>* new_node = new Node<T> { std::move(value) };
  new_node->next = head_;

  if (!this->empty())
  {
    head_->prev = new_node;
    head_ = new_node;
  }
  else
    *(head_ = tail_ = new_node);

  ++size_;

  return *this;
}

template <typename T>
DoubleLinkedList<T>& DoubleLinkedList<T>::pop_front()
{
  if (this->empty()) throw std::out_of_range("Lista je prazna");

  auto temp = head_;
  if (head_->next != nullptr)
  {
    head_ = head_->next;
    head_->prev = nullptr;
  }
  else
    head_ = tail_ = nullptr;

  delete temp;
  --size_;

  return *this;
}

template <typename T>
DoubleLinkedList<T>& DoubleLinkedList<T>::pop_back()
{
  if (this->empty()) throw std::out_of_range("Lista je prazna");

  auto temp = tail_;
  if (tail_->prev != nullptr)
  {
    tail_ = tail_->prev;
    tail_->next = nullptr;
  }
  else
    tail_ = head_ = nullptr;

  delete temp;
  --size_;

  return *this;
}

template <typename T>
T& DoubleLinkedList<T>::front()
{
  if (this->empty()) throw std::out_of_range("Lista je prazna");
  return head_->data;
}

template <typename T>
const T& DoubleLinkedList<T>::front() const
{
  if (this->empty()) throw std::out_of_range("Lista je prazna");
  return head_->data;
}

template <typename T>
T& DoubleLinkedList<T>::back()
{
  if (this->empty()) throw std::out_of_range("Lista je prazna");
  return tail_->data;
}

template <typename T>
const T& DoubleLinkedList<T>::back() const
{
  if (this->empty()) throw std::out_of_range("Lista je prazna");
  return tail_->data;
}

template <typename T>
void DoubleLinkedList<T>::clear()
{
  dealoc();
  head_ = tail_ = nullptr;
  size_ = 0;
}

template <typename T>
typename DoubleLinkedList<T>::Iterator DoubleLinkedList<T>::insert(Iterator pos, const T& element)
{
  auto new_node = new Node<T> { element };

  if (this->empty())
  {
    ++size_;
    return Iterator { head_ = tail_ = new_node };
  }

  new_node->prev = pos.node_->prev;
  new_node->next = pos.node_;
  pos.node_->prev = new_node;
  ++size_;

  if (pos.node_->next != nullptr)
    pos.node_->next->prev = new_node;
  if (pos.node_ == head_)
    head_ = new_node;
  if (pos.node_ == tail_)
    tail_ = new_node;

  return Iterator { new_node };
}

template <typename T>
typename DoubleLinkedList<T>::Iterator DoubleLinkedList<T>::erase(Iterator pos)
{
  if (this->empty()) return Iterator { nullptr };

  if (this->size_ == 1)
  {
    --size_;
    delete pos.node_;
    head_ = tail_ = nullptr;
    return Iterator { nullptr };
  }

  --size_;
  if (pos.node_->next == nullptr)
  {
    pos.node_->prev->next = nullptr;
    delete pos.node_;
    return Iterator { nullptr };
  }

  if (pos.node_->prev == nullptr)
  {
    pos.node_->next->prev = nullptr;
    delete pos.node_;
    return Iterator { nullptr };
  }

  Node<T>* temp = pos.node_->next;
  pos.node_->prev->next = pos.node_->next;
  pos.node_->next->prev = pos.node_->prev;
  delete pos.node_;

  return Iterator { temp };
}

template <typename T>
typename DoubleLinkedList<T>::Iterator DoubleLinkedList<T>::erase(Iterator beginIt, Iterator endIt)
{
  if (this->empty()) return Iterator { nullptr };

  if (beginIt == this->begin() && endIt == this->end())
  {
    this->clear();
    return Iterator { nullptr };
  }

  if (endIt != this->end())
  {
    endIt.node_->prev = beginIt.node_->prev;
    if (beginIt != this->begin())
      beginIt.node_->prev->next = endIt.node_;
  }
  else
  {
    beginIt.node_->prev->next = nullptr;
    tail_ = beginIt.node_->prev;
  }

  if (beginIt != this->begin())
  {
    beginIt.node_->prev->next = endIt.node_;
    if (endIt != this->end())
      endIt.node_->prev = beginIt.node_->prev;
  }
  else
  {
    endIt.node_->prev = nullptr;
    head_ = endIt.node_;
  }

  Node<T>* temp;
  while (beginIt != endIt)
  {
    temp = beginIt.node_;
    ++beginIt;
    --size_;
    delete temp;
  }

  return endIt;
}

template <typename T>
void DoubleLinkedList<T>::remove_if(std::function<bool(const T&)>&& p)
{
  Iterator temp;
  for (auto it = this->begin(); it != this->end(); ++it)
  {
    if (p(*it))
    {
      erase(it);
      it = temp;
    }
    temp = it;
  }
}

template <typename T>
void DoubleLinkedList<T>::reverse()
{
  Iterator it_l = head_;
  Iterator it_r = tail_;

  while (it_l.node_->next != it_r.node_->prev)
  {
    std::swap(*it_l++, *it_r--);
    if (it_l.node_->next != it_r.node_) break;
  }
}

template <typename T>
typename DoubleLinkedList<T>::Iterator DoubleLinkedList<T>::find(const T& element) const
{
  for (auto it = this->begin(); it != this->end(); ++it)
    if (*it == element)
      return it;
  return this->end();
}

template <typename T>
void DoubleLinkedList<T>::dealoc()
{
  Iterator prev;
  Iterator it = this->begin();
  while (it != this->end())
  {
    prev = it++;
    delete prev.node_;
  }
}

template <typename T>
DoubleLinkedList<T>::Iterator::Iterator(const Iterator& other)
{
  this->node_ = other.node_;
}

template <typename T>
DoubleLinkedList<T>::Iterator::Iterator(Iterator&& other)
{
  this->node_ = std::move(other.node_);
  other.node_ = nullptr;
}

template <typename T>
typename DoubleLinkedList<T>::Iterator& DoubleLinkedList<T>::Iterator::operator=(const Iterator& other)
{
  this->node_ = other.node_;
  return *this;
}

template <typename T>
typename DoubleLinkedList<T>::Iterator& DoubleLinkedList<T>::Iterator::operator=(Iterator&& other)
{
  if (this != &other)
  {
    this->node_ = std::move(other.node_);
    other.node_ = nullptr;
  }
  return *this;
}

template <typename T>
typename DoubleLinkedList<T>::Iterator DoubleLinkedList<T>::Iterator::operator++(int)
{
  auto temp = this->node_;
  this->node_ = this->node_->next;
  return temp;
}

template <typename T>
typename DoubleLinkedList<T>::Iterator& DoubleLinkedList<T>::Iterator::operator++()
{
  this->node_ = this->node_->next;
  return *this;
}

template <typename T>
typename DoubleLinkedList<T>::Iterator DoubleLinkedList<T>::Iterator::operator--(int)
{
  auto temp = this->node_;
  this->node_ = this->node_->prev;
  return temp;
}

template <typename T>
typename DoubleLinkedList<T>::Iterator& DoubleLinkedList<T>::Iterator::operator--()
{
  this->node_ = this->node_->prev;
  return *this;
}
