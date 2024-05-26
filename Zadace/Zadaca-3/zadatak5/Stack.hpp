#pragma once

#include <algorithm>
#include <stddef.h>
#include <stdexcept>
#include <utility>

template <typename T>
class Stack
{
  public:
    Stack();
    Stack(const Stack&);
    Stack(Stack&&);
    Stack& operator=(const Stack&);
    Stack& operator=(Stack&&);
    ~Stack();
    T pop();
    T& top() const;
    template <typename U>
    Stack<T>& push(U&&);
    size_t size() const { return size_; }
    size_t capacity() const { return capacity_; }
    bool empty() const { return size_ == 0; }
    bool full() const { return size_ == capacity_; }
    void clear();
    void resize(size_t newSize);
    bool operator==(const Stack&);
    bool operator!=(const Stack&);

  private:
    void realoc();
    void realoc(size_t);
    size_t capacity_ { 0 };
    size_t size_ { 0 };
    T* arr_ { nullptr };
};

template <typename T>
Stack<T>::Stack() : capacity_ { 10 }, size_ { 0 }, arr_ { new T[capacity_] } { }

template <typename T>
Stack<T>::Stack(const Stack& other)
  : capacity_ { other.capacity_ }, size_ { other.size_ }, arr_ { new T[capacity_] }
{
  std::copy(other.arr_, other.arr_ + other.size_, this->arr_);
}

template <typename T>
Stack<T>::Stack(Stack&& other)
  : capacity_ { other.capacity_ }, size_ { other.size_ }, arr_ { new T[capacity_] }
{
  std::move(other.arr_, other.arr_ + other.size_, this->arr_);
  other.clear();
}

template <typename T>
Stack<T>& Stack<T>::operator=(const Stack& other)
{
  if (this != &other)
  {
    this->capacity_ = other.capacity_;
    this->size_ = other.size_;

    delete[] this->arr_;
    this->arr_ = new T[capacity_];
    std::copy(other.arr_, other.arr_ + other.size_, this->arr_);
  }
  return *this;
}

template <typename T>
Stack<T>& Stack<T>::operator=(Stack&& other)
{
  if (this != &other)
  {
    this->capacity_ = other.capacity_;
    this->size_ = other.size_;

    delete[] this->arr_;
    this->arr_ = new T[capacity_];
    std::move(other.arr_, other.arr_ + other.size_, this->arr_);

    other.clear();
  }
  return *this;
}

template <typename T>
Stack<T>::~Stack()
{
  clear();
  this->capacity_ = 0;
}

template <typename T>
T Stack<T>::pop()
{
  if (this->empty()) throw std::out_of_range("Stack je prazan.");
  return arr_[--size_];
}

template <typename T>
T& Stack<T>::top() const
{
  if (this->empty()) throw std::out_of_range("Stack je prazan.");
  return arr_[size_ - 1];
}

template <typename T>
template <typename U>
Stack<T>& Stack<T>::push(U&& value)
{
  if (this->full()) realoc();
  arr_[size_++] = std::forward<U>(value);
  return *this;
}

template <typename T>
void Stack<T>::clear()
{
  delete[] arr_;
  arr_ = nullptr;
  size_ = 0;
}

template <typename T>
void Stack<T>::resize(size_t newSize)
{
  if (newSize > capacity_) realoc(newSize);
  size_ = newSize;
  for (int i = size_; i < newSize; ++i)
    arr_[i] = 0;
}

template <typename T>
bool Stack<T>::operator==(const Stack& other)
{
  if (this->size_ != other.size_) return false;
  for (int i = 0; i < this->size_; ++i)
    if (this->arr_[i] != other.arr_[i]) return false;
  return true;
}

template <typename T>
bool Stack<T>::operator!=(const Stack& other)
{
  if (this->size_ != other.size_) return true;
  if (this->empty() && other.empty()) return false;
  for (int i = 0; i < this->size_; ++i)
    if (this->arr_[i] == other.arr_[i]) return false;
  return true;
}

template <typename T>
void Stack<T>::realoc() { realoc(this->capacity_ * 2); }

template <typename T>
void Stack<T>::realoc(size_t new_capacity)
{
  T* new_arr = new T[new_capacity];
  std::move(this->arr_, this->arr_ + size_, new_arr);
  delete[] this->arr_;
  this->arr_ = new_arr;
  this->capacity_ = new_capacity;
}
