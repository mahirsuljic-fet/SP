#pragma once

#include <iostream>
#include <iterator>
#include <stdexcept>
#include <utility>

template <typename T>
class List
{
  public:
    List() = default;
    List(const List& other);
    List(List&& other);
    List& operator=(const List& other);
    List& operator=(List&& other);
    ~List();

    void push_back(const T& element);
    void push_front(const T& element);
    void push_back(T&& element);
    void push_front(T&& element);

    void print() const;

    // T& front();
    // T& back();
    // T& front() const;
    // T& back() const;

    size_t size() const;
    void clear();

    bool empty() const;
    void pop_front();
    void pop_back();

    const T& at(size_t index) const;

    class iterator;
    iterator begin()
    {
    }
    iterator end()
    {
    }

    void insert(iterator position, const T& element);
    void insert(iterator position, T&& element);

    void erase(iterator position);

  private:
    struct Node
    {
        Node(const T& v, Node* ptr = nullptr) : value { v }, next { ptr } { }
        Node(T&& v, Node* ptr = nullptr) : value { std::move(v) }, next { ptr } { }
        T value;
        Node* next;
    };

    Node* head_ = nullptr;
    Node* tail_ = nullptr;
    size_t size_ = 0;
};

template <typename T>
class List<T>::iterator : public std::iterator<std::forward_iterator_tag, T>
{
  public:
    friend class List<T>;

    iterator(Node* p) : p_ { p }
    {
    }

    iterator& operator++()
    {
    }

    iterator operator++(int)
    {
    }

    bool operator==(const iterator& other)
    {
    }

    bool operator!=(const iterator& other)
    {
    }

    T& operator*()
    {
    }

    T* operator->()
    {
    }

  private:
    Node* p_;
};

template <typename T>
void List<T>::push_back(const T& element)
{
  std::cout << "push_back const T&" << std::endl;
  auto temp = new Node { element };
  if (size_ == 0)
    head_ = tail_ = temp;
  else
    tail_ = tail_->next = temp;
  ++size_;
}

template <typename T>
void List<T>::push_front(const T& element)
{
  std::cout << "push_front const T&" << std::endl;
  auto temp = new Node { element };
  if (size_ == 0)
    head_ = tail_ = temp;
  else
  {
    temp->next = head_;
    head_ = temp;
  }
  ++size_;
}

template <typename T>
void List<T>::push_back(T&& element)
{
  std::cout << "push_back T&&" << std::endl;
  if (head_ == nullptr)
  {
    head_ = new Node(std::move(element), nullptr);
    tail_ = head_;
  }
  else
  {
    tail_->next = new Node(std::move(element));
    tail_ = tail_->next;
  }
  size_++;
}

template <typename T>
void List<T>::push_front(T&& element)
{
  std::cout << "push_front T&&" << std::endl;
  head_ = new Node(std::move(element), head_);
  if (tail_ == nullptr)
    tail_ = head_;
  size_++;
}

template <typename T>
size_t List<T>::size() const
{
  return size_;
}

template <typename T>
bool List<T>::empty() const
{
  return size_ == 0;
}

template <typename T>
void List<T>::print() const
{
  auto temp = head_;
  while (temp != nullptr)
  {
    std::cout << temp->value << " ";
    temp = temp->next;
  }
}

template <typename T>
void List<T>::clear()
{
  // moze se izvrsit optimizacija tako da se koriste
  // head_ i tail_ umjesto temp varijabli
  auto temp = head_;
  while (temp != nullptr)
  {
    auto next = temp->next;
    delete temp;
    temp = next;
  }
  head_ = tail_ = nullptr;
  size_ = 0;
}

template <typename T>
List<T>::List(const List& other)
{
  auto temp = other.head_;
  while (temp != nullptr)
  {
    push_back(temp->value);
    temp = temp->next;
  }
}

template <typename T>
List<T>::List(List&& other)
  : head_ { other.head_ }, tail_ { other.tail_ }, size_ { other.size_ }
{
  other.head_ = other.tail_ = nullptr;
  other.size_ = 0;
}

template <typename T>
List<T>& List<T>::operator=(const List& other)
{
  if (this == &other) return *this;

  clear();
  for (auto temp = other.head_; temp != nullptr; temp = temp->next)
    push_back(temp->value);
  return *this;
}

template <typename T>
List<T>& List<T>::operator=(List&& other)
{
  std::swap(head_, other.head_);
  std::swap(tail_, other.tail_);
  std::swap(size_, other.size_);
  return *this;
}

template <typename T>
List<T>::~List()
{
  clear();
}

template <typename T>
void List<T>::pop_front()
{
  auto temp = head_;
  head_ = head_->next;
  delete temp;
  --size_;
  if (size_ == 0)
    tail_ = nullptr;
}

template <typename T>
void List<T>::pop_back()
{
  auto temp = head_;
  if (size_ == 0) return;
  if (size_ == 1) return clear();
  // while (temp->next->next != nullptr) temp = temp->next;
  while (temp->next != tail_) temp = temp->next;
  delete tail_;
  tail_ = temp;
  tail_->next = nullptr;
  --size_;
}

// slozenost O(n)
template <typename T>
const T& List<T>::at(size_t index) const
{
  if (index >= size_) throw std::out_of_range("Indeks nije validan");

  auto temp = head_;
  for (int i = 0; i < index; ++i)
    temp = temp->next;
  return temp->value;
}

// O(n)
template <typename T>
void List<T>::insert(iterator position, const T& element)
{
}
// O(1)

// O(n)
template <typename T>
void List<T>::erase(iterator position)
{
}
// O(1)??
