#pragma once

#include <algorithm>
#include <cstddef>
#include <iostream>
#include <iterator>
#include <stdexcept>
#include <type_traits>

template <typename T>
class Array
{
  public:
    Array() : capacity_ { 100 }, data_ { new T[100] }, size_ { 0 } { }

    Array(const std::size_t capacity)
      : capacity_ { capacity }, data_ { new T[capacity_] }, size_ { 0 } { }

    Array(const Array& other)
      : capacity_ { other.capacity_ }, data_ { new T[capacity_] }, size_ { other.size_ }
    {
      std::cout << "copy ctor" << std::endl;
      std::copy(other.data_, other.data_ + other.size_, data_);
    }

    Array(Array&& other)
      : capacity_ { other.capacity_ }, data_ { other.data_ }, size_ { other.size_ }
    {
      std::cout << "move ctor" << std::endl;
      other.data_ = nullptr;
      other.capacity_ = other.size_ = 0;
    }

    // Standardna implementacija
    Array& operator=(const Array& other)
    {
      std::cout << "copy=" << std::endl;
      if (this != &other)
      {
        delete[] data_;
        data_ = new T[other.capacity_];
        std::copy(other.data_, other.data_ + other.size_, data_);
        capacity_ = other.capacity_;
        size_ = other.size_;
      }
      return *this;
    }

    // Standardna implementacija
    Array& operator=(Array&& other)
    {
      if (this != &other)
      {
        delete[] data_;
        data_ = other.data_;
        capacity_ = other.capacity_;
        size_ = other.size_;
        other.data_ = nullptr;
        other.capacity_ = other.size_ = 0;
      }
      return *this;
    }

    ~Array() { delete[] data_; }

    void push_back(const T& element);
    void push_back(T&& element);

    T& operator[](size_t index) { return data_[index]; }

    const T& operator[](size_t index) const { return data_[index]; }

    T& at(size_t index)
    {
      if (index >= size_) throw std::out_of_range { "Nevalidan indeks!" };
      return data_[index];
    }

    const T& at(size_t index) const
    {
      if (index >= size_) throw std::out_of_range { "Nevalidan indeks!" };
      return data_[index];
    }

    T& front() { return data_[0]; }
    const T& front() const { return data_[0]; }
    T& back() { return data_[size_ - 1]; }
    const T& back() const { return data_[size_ - 1]; }

    void pop_back()
    {
      // back() = T();
      auto temp = std::move(back());
      --size_;
    }

    void clear()
    {
      delete[] data_;
      data_ = new T[capacity_];
      size_ = 0;
    }

    bool empty() const { return size_ == 0; }
    size_t size() const { return size_; }

    class Iterator;

    Iterator begin() { return Iterator { data_ }; }
    Iterator end() { return Iterator { data_ + size_ }; }

    void resize(size_t new_size, const T& value)
    {
      if (size_ < new_size)
      {
        if (new_size > capacity_)
          reallocate(new_size);

        for (auto i = size_; i < new_size; ++i)
        {
          data_[i] = value;
          // push_back(value);
        }
        size_ = new_size;
      }
      else
        size_ = new_size;
    }

    void insert(Iterator it, const T& value);
    void erase(Iterator it);

  private:
    std::size_t capacity_;
    T* data_;
    std::size_t size_;
    void reallocate(size_t new_capacity)
    {
      auto temp = new T[new_capacity];
      for (int i = 0; i < size_; ++i)
        temp[i] = std::move(data_[i]);
      delete[] data_;
      data_ = temp;
      capacity_ = new_capacity;
    }
};

template <typename T>
void Array<T>::push_back(const T& element)
{
  std::cout << "copy push_back" << std::endl;
  if (size_ == capacity_) // throw std::out_of_range { "Reallocate" };
    reallocate(2 * capacity_);
  data_[size_++] = element;
}

template <typename T>
void Array<T>::push_back(T&& element)
{
  std::cout << "move push_back" << std::endl;
  if (size_ == capacity_) // throw std::out_of_range { "Reallocate" };
    reallocate(2 * capacity_);
  data_[size_++] = std::move(element);
}

template <typename T>
class Array<T>::Iterator
{
  public:
    using iterator_category = std::random_access_iterator_tag;
    using value_type = T;
    using pointer = T*;
    using reference = T&;
    using difference_type = ptrdiff_t;

    Iterator(T* p) : ptr_ { p } { }

    Iterator& operator++()
    {
      ++ptr_;
      return *this;
    }

    Iterator operator++(int) { return Iterator { ptr_++ }; }

    Iterator& operator--()
    {
      --ptr_;
      return *this;
    }

    Iterator operator--(int) { return Iterator { ptr_-- }; }

    bool operator!=(const Iterator& rhs) const { return ptr_ != rhs.ptr_; }

    bool operator==(const Iterator& rhs) const { return ptr_ == rhs.ptr_; }

    T& operator*() { return *ptr_; }

    long operator-(const Iterator& rhs) const { return ptr_ - rhs.ptr_; }

    Iterator operator+(int n) const { return Iterator { ptr_ + n }; }
    Iterator operator-(int n) const { return Iterator { ptr_ - n }; }
    bool operator<(const Iterator& rhs) const { return ptr_ < rhs.ptr_; }
    bool operator>(const Iterator& rhs) const { return ptr_ > rhs.ptr_; }
    bool operator<=(const Iterator& rhs) const { return ptr_ <= rhs.ptr_; }
    bool operator>=(const Iterator& rhs) const { return ptr_ >= rhs.ptr_; }

  private:
    T* ptr_;
};

template <typename T>
void Array<T>::insert(Iterator it, const T& value)
{
  if (size_ == capacity_)
    reallocate(2 * capacity_);
  for (auto i = end() - 1; i >= it; --i)
    *(i + 1) = std::move(*i);
  *it = value;
  ++size_;
}

template <typename T>
void Array<T>::erase(Iterator it)
{
  for (auto i = it; i < end() - 1; ++i)
    *i = std::move(*(i + 1));
  --size_;
}
