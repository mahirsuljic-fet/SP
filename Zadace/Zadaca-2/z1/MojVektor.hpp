#pragma once

#include <algorithm>
#include <cstddef>
#include <initializer_list>
#include <iostream>
#include <sstream>
#include <stdexcept>
#include <string>

template <typename T>
class MojVektor
{
  public:
    class Iterator;

    MojVektor();
    MojVektor(const std::initializer_list<T>&);
    MojVektor(const MojVektor&);
    MojVektor& operator=(const MojVektor&);
    MojVektor(MojVektor&&);
    MojVektor& operator=(MojVektor&&);
    ~MojVektor();

    MojVektor& push_back(const T&);
    MojVektor& push_front(const T&);
    MojVektor& push_back(T&&);
    MojVektor& push_front(T&&);
    MojVektor& pop_back();
    MojVektor& pop_front();
    MojVektor subvector(Iterator begin, Iterator end);

    size_t size() const;
    size_t capacity() const;
    T* data();
    T& at(size_t) const;
    T& operator[](size_t) const;
    T& back() const;
    T& front() const;
    bool operator==(const MojVektor&) const;
    bool operator!=(const MojVektor&) const;
    bool full() const;
    bool empty() const;

    void clear();
    void rotate();
    void rotate(Iterator beginIt, Iterator endIt);
    void resize(size_t newSize, const T& difference_value);
    void reserve(size_t capacity);

    Iterator begin() const;
    Iterator end() const;
    Iterator find(const T&) const;
    Iterator erase(Iterator pos);
    Iterator insert(Iterator, const T&);
    Iterator insert(Iterator, T&&);
    Iterator rbegin() const;
    Iterator rend() const;
    Iterator erase(Iterator beginIt, Iterator endIt);

    template <typename U>
    friend std::ostringstream& operator<<(std::ostringstream&, const MojVektor<U>&);

  private:
    void realoc();
    size_t capacity_;
    size_t size_;
    T* arr_;
};

template <typename T>
class MojVektor<T>::Iterator
{
  public:
    using iterator_category = std::random_access_iterator_tag;
    using value_type = T;
    using pointer = T*;
    using reference = T&;
    using difference_type = long;

    Iterator() : ptr_ { nullptr } { }
    Iterator(T* p) : ptr_ { p } { }
    Iterator(const Iterator&);
    Iterator(Iterator&&);
    Iterator& operator=(const Iterator&);
    Iterator& operator=(Iterator&&);

    T& operator*();
    T* operator->();
    T* operator[](size_t);
    bool operator==(const Iterator&);
    bool operator!=(const Iterator&);
    bool operator>(const Iterator&);
    bool operator<(const Iterator&);
    bool operator>=(const Iterator&);
    bool operator<=(const Iterator&);

    Iterator& operator++();
    Iterator operator++(int);
    Iterator& operator--();
    Iterator operator--(int);
    Iterator operator+(difference_type);
    Iterator operator-(difference_type);
    Iterator& operator+=(difference_type);
    Iterator& operator-=(difference_type);

    friend Iterator operator+(difference_type n, const Iterator& it) { return Iterator { it.ptr_ + n }; }
    friend Iterator operator-(difference_type n, const Iterator& it) { return Iterator { it.ptr_ - n }; }
    friend difference_type operator-(const Iterator& lhs, const Iterator& rhs) { return lhs.ptr_ - rhs.ptr_; }

  private:
    T* ptr_ = nullptr;
};

template <typename T>
MojVektor<T>::MojVektor() : capacity_ { 10 }, size_ { 0 }, arr_ { new T[capacity_] } { }

template <typename T>
MojVektor<T>::MojVektor(const std::initializer_list<T>& list)
  : capacity_ { list.size() }, size_ { list.size() }, arr_ { new T[capacity_] }
{
  std::copy(list.begin(), list.end(), arr_);
}

template <typename T>
MojVektor<T>::MojVektor(const MojVektor<T>& other)
{
  capacity_ = other.capacity_;
  size_ = other.size_;
  arr_ = new T[capacity_];

  std::copy(other.arr_, other.arr_ + other.size_, arr_);
}

template <typename T>
MojVektor<T>& MojVektor<T>::operator=(const MojVektor<T>& other)
{
  if (this != &other)
  {
    delete[] arr_;

    this->capacity_ = other.capacity_;
    this->size_ = other.size_;
    this->arr_ = new T[capacity_];

    std::copy(other.arr_, other.arr_ + other.size_, arr_);
  }

  return *this;
}

template <typename T>
MojVektor<T>::MojVektor(MojVektor<T>&& other)
{
  capacity_ = other.capacity_;
  size_ = other.size_;
  arr_ = other.arr_;

  other.capacity_ = 0;
  other.size_ = 0;
  other.arr_ = nullptr;
}

template <typename T>
MojVektor<T>& MojVektor<T>::operator=(MojVektor<T>&& other)
{
  if (this != &other)
  {
    delete[] arr_;

    capacity_ = other.capacity_;
    size_ = other.size_;
    arr_ = other.arr_;

    other.capacity_ = 0;
    other.size_ = 0;
    other.arr_ = nullptr;
  }

  return *this;
}

template <typename T>
MojVektor<T>::~MojVektor()
{
  delete[] arr_;

  size_ = 0;
  capacity_ = 0;
  arr_ = nullptr;
}

template <typename T>
MojVektor<T>& MojVektor<T>::push_back(const T& element)
{
  if (size_ == capacity_)
  {
    capacity_ *= 2;
    realoc();
  }

  arr_[size_++] = element;

  return *this;
}

template <typename T>
MojVektor<T>& MojVektor<T>::push_front(const T& element)
{
  if (size_ == capacity_)
  {
    capacity_ *= 2;
    realoc();
  }

  std::move_backward(arr_, arr_ + size_, arr_ + size_ + 1);

  arr_[0] = element;
  ++size_;

  return *this;
}

template <typename T>
MojVektor<T>& MojVektor<T>::push_back(T&& element)
{
  if (size_ == capacity_)
  {
    capacity_ *= 2;
    realoc();
  }

  arr_[size_++] = std::move(element);

  return *this;
}

template <typename T>
MojVektor<T>& MojVektor<T>::push_front(T&& element)
{
  if (size_ == capacity_)
  {
    capacity_ *= 2;
    realoc();
  }
  else
    std::move_backward(arr_, arr_ + size_, arr_ + size_ + 1);

  arr_[0] = std::move(element);
  ++size_;

  return *this;
}

template <typename T>
MojVektor<T>& MojVektor<T>::pop_back()
{
  if (size_ == 0) throw std::out_of_range("Vektor je prazan.");
  --size_;
  return *this;
}

template <typename T>
MojVektor<T>& MojVektor<T>::pop_front()
{
  if (size_ == 0) throw std::out_of_range("Vektor je prazan.");
  std::move(arr_ + 1, arr_ + size_, arr_);
  --size_;
  return *this;
}

template <typename T>
MojVektor<T> MojVektor<T>::subvector(MojVektor<T>::Iterator begin, MojVektor<T>::Iterator end)
{
  MojVektor<T> subvec;

  subvec.size_ = end - begin;
  subvec.capacity_ = subvec.size_;
  subvec.arr_ = new T[subvec.size_];

  std::copy(begin, end, subvec.arr_);

  return subvec;
}

template <typename T>
size_t MojVektor<T>::size() const { return size_; }

template <typename T>
size_t MojVektor<T>::capacity() const { return capacity_; }

template <typename T>
T* MojVektor<T>::data() { return arr_; }

template <typename T>
T& MojVektor<T>::at(size_t index) const
{
  if (index >= size_) throw std::out_of_range("Indeks je van opsega vektora");
  return arr_[index];
}

template <typename T>
T& MojVektor<T>::operator[](size_t index) const { return arr_[index]; }

template <typename T>
T& MojVektor<T>::back() const
{
  if (size_ == 0) throw std::out_of_range("Vektor je prazan.");
  return arr_[size_ - 1];
}

template <typename T>
T& MojVektor<T>::front() const
{
  if (size_ == 0) throw std::out_of_range("Vektor je prazan.");
  return arr_[0];
}

template <typename T>
bool MojVektor<T>::operator==(const MojVektor& other) const
{
  if (this->size_ != other.size_) return false;

  for (size_t i = 0; i < this->size_; ++i)
    if (this->arr_[i] != other.arr_[i])
      return false;

  return true;
}

template <typename T>
bool MojVektor<T>::operator!=(const MojVektor& other) const { return !(*this == other); }

template <typename T>
bool MojVektor<T>::full() const { return size_ == capacity_; }

template <typename T>
bool MojVektor<T>::empty() const { return size_ == 0; }

template <typename T>
void MojVektor<T>::clear()
{
  delete[] arr_;

  size_ = 0;
  capacity_ = 0;
  arr_ = nullptr;
}

template <typename T>
void MojVektor<T>::rotate()
{
  for (size_t i = 0; i < size_ / 2; ++i)
    std::swap(arr_[i], arr_[size_ - i - 1]);
}

template <typename T>
void MojVektor<T>::rotate(MojVektor<T>::Iterator beginIt, MojVektor<T>::Iterator endIt)
{
  auto middleIt = beginIt + (endIt - beginIt) / 2;
  while (beginIt != middleIt)
    std::swap(*beginIt++, *--endIt);
}

template <typename T>
void MojVektor<T>::resize(size_t newSize, const T& difference_value)
{
  if (newSize < size_)
  {
    size_ = newSize;
    return;
  }

  if (newSize > capacity_)
  {
    capacity_ = newSize;
    realoc();

    for (size_t i = size_; i < newSize; ++i)
      arr_[i] = difference_value;

    size_ = newSize;
  }
}

template <typename T>
void MojVektor<T>::reserve(size_t new_capacity)
{
  if (new_capacity > capacity_)
  {
    capacity_ = new_capacity;
    T* temp = new T[capacity_];
    std::move(begin(), end(), temp);
    delete[] arr_;
    arr_ = temp;
  }
}

template <typename T>
typename MojVektor<T>::Iterator MojVektor<T>::begin() const { return Iterator { arr_ }; }

template <typename T>
typename MojVektor<T>::Iterator MojVektor<T>::end() const { return Iterator { arr_ + size_ }; }

template <typename T>
typename MojVektor<T>::Iterator MojVektor<T>::find(const T& element) const
{
  auto it = this->begin();
  const auto end = this->end();

  while (it != end)
  {
    if (*it == element)
      return it;
    ++it;
  }

  return it;
}

template <typename T>
typename MojVektor<T>::Iterator MojVektor<T>::erase(MojVektor<T>::Iterator pos)
{
  if (pos < this->end())
  {
    std::move(pos + 1, this->end(), pos);
    --size_;
  }

  return pos;
}

template <typename T>
typename MojVektor<T>::Iterator MojVektor<T>::insert(MojVektor<T>::Iterator pos, const T& element)
{
  if (pos < this->begin() || pos >= this->end()) throw std::out_of_range("Pozicija nije validna");

  if (size_ == capacity_)
  {
    typename MojVektor<T>::Iterator::difference_type offset = pos - this->begin();
    capacity_ *= 2;
    realoc();
    pos = this->begin() + offset;
  }

  std::move_backward(pos, this->end(), this->end() + 1);
  *pos = element;
  ++size_;

  return pos;
}

template <typename T>
typename MojVektor<T>::Iterator MojVektor<T>::insert(MojVektor<T>::Iterator pos, T&& element)
{
  if (pos < this->begin() || pos >= this->end()) throw std::out_of_range("Pozicija nije validna");

  if (size_ == capacity_)
  {
    typename MojVektor<T>::Iterator::difference_type offset = pos - this->begin();
    capacity_ *= 2;
    realoc();
    pos = this->begin() + offset;
  }

  std::move_backward(pos, this->end(), this->end() + 1);
  *pos = std::move(element);
  ++size_;

  return pos;
}

template <typename T>
typename MojVektor<T>::Iterator MojVektor<T>::rbegin() const { return arr_ + size_ - 1; }

template <typename T>
typename MojVektor<T>::Iterator MojVektor<T>::rend() const { return arr_ - 1; }

template <typename T>
typename MojVektor<T>::Iterator MojVektor<T>::erase(MojVektor<T>::Iterator beginIt, MojVektor<T>::Iterator endIt)
{
  std::move(this->end() - (this->end() - endIt), this->end(), beginIt);
  size_ -= endIt - beginIt;
  return beginIt;
}

template <typename T>
void MojVektor<T>::realoc()
{
  T* temp = new T[this->capacity_];
  std::move(this->begin(), this->end(), temp);
  delete[] arr_;
  arr_ = temp;
}

template <typename T>
std::ostringstream& operator<<(std::ostringstream& oss, const MojVektor<T>& vec)
{
  oss << "{";

  if (!vec.empty())
  {
    auto it = vec.begin();
    auto last = vec.end() - 1;
    while (it != last) oss << *it++ << ", ";
    oss << *it;
  }

  oss << "}";

  return oss;
}

template <typename T>
MojVektor<T>::Iterator::Iterator(const MojVektor<T>::Iterator& other) { this->ptr_ = other.ptr_; }

template <typename T>
MojVektor<T>::Iterator::Iterator(MojVektor<T>::Iterator&& other)
{
  this->ptr_ = other.ptr_;
  other.ptr_ = nullptr;
}

template <typename T>
typename MojVektor<T>::Iterator& MojVektor<T>::Iterator::operator=(const MojVektor<T>::Iterator& other)
{
  this->ptr_ = other.ptr_;
  return *this;
}

template <typename T>
typename MojVektor<T>::Iterator& MojVektor<T>::Iterator::operator=(MojVektor<T>::Iterator&& other)
{
  if (this != &other)
  {
    this->ptr_ = other.ptr_;
    other.ptr_ = nullptr;
  }

  return *this;
}

template <typename T>
T& MojVektor<T>::Iterator::operator*() { return *ptr_; }

template <typename T>
T* MojVektor<T>::Iterator::operator->() { return ptr_; }

template <typename T>
T* MojVektor<T>::Iterator::operator[](size_t index) { return ptr_ + index; }

template <typename T>
bool MojVektor<T>::Iterator::operator==(const MojVektor<T>::Iterator& other) { return this->ptr_ == other.ptr_; }

template <typename T>
bool MojVektor<T>::Iterator::operator!=(const MojVektor<T>::Iterator& other) { return this->ptr_ != other.ptr_; }

template <typename T>
bool MojVektor<T>::Iterator::operator>(const MojVektor<T>::Iterator& other) { return this->ptr_ > other.ptr_; }

template <typename T>
bool MojVektor<T>::Iterator::operator<(const MojVektor<T>::Iterator& other) { return this->ptr_ < other.ptr_; }

template <typename T>
bool MojVektor<T>::Iterator::operator>=(const MojVektor<T>::Iterator& other) { return this->ptr_ >= other.ptr_; }

template <typename T>
bool MojVektor<T>::Iterator::operator<=(const MojVektor<T>::Iterator& other) { return this->ptr_ <= other.ptr_; }

template <typename T>
typename MojVektor<T>::Iterator& MojVektor<T>::Iterator::operator++()
{
  ++ptr_;
  return *this;
}

template <typename T>
typename MojVektor<T>::Iterator MojVektor<T>::Iterator::operator++(int)
{
  T* temp = ptr_++;
  return temp;
}

template <typename T>
typename MojVektor<T>::Iterator& MojVektor<T>::Iterator::operator--()
{
  --ptr_;
  return *this;
}

template <typename T>
typename MojVektor<T>::Iterator MojVektor<T>::Iterator::operator--(int)
{
  T* temp = ptr_--;
  return temp;
}

template <typename T>
typename MojVektor<T>::Iterator MojVektor<T>::Iterator::operator+(difference_type n) { return Iterator { ptr_ + n }; }

template <typename T>
typename MojVektor<T>::Iterator MojVektor<T>::Iterator::operator-(difference_type n) { return Iterator { ptr_ - n }; }

template <typename T>
typename MojVektor<T>::Iterator& MojVektor<T>::Iterator::operator+=(difference_type n)
{
  ptr_ += n;
  return *this;
}

template <typename T>
typename MojVektor<T>::Iterator& MojVektor<T>::Iterator::operator-=(difference_type n)
{
  ptr_ -= n;
  return *this;
}
