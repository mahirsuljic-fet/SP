#pragma once

#include <algorithm>
#include <cstdlib>
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

      // Drugi nacin
      // for i = 0 do size_
      //   push_back(other[i])

      // Treci nacin
      // for (auto i = 0u; i < size_; i++) {
      //   data_[i] = other.data_[i];
      // }

      // Cetvrti nacin
      // auto dest = data_;
      // for (auto source = other.data_; source < other.data_ + other.size_;
      //      source++)
      //   *dest++ = *source;
    }

    Array(Array&& other)
      : capacity_ { other.capacity_ }, data_ { other.data_ }, size_ { other.size_ }
    {
      std::cout << "move ctor" << std::endl;
      other.data_ = nullptr;
      other.capacity_ = other.size_ = 0;
    }

    // Standardna implementacija
    // Array& operator=(const Array& other)
    // {
    //   if (this == &other) return *this;
    //
    //   delete[] data_;
    //
    //   size_ = other.size_;
    //   capacity_ = other.capacity_;
    //
    //   data_ = new T[capacity_];
    //   std::copy(other.data_, other.data_ + other.size_, data_);
    //
    //   return *this;
    // }

    // Alternativna implementacija
    Array& operator=(const Array& other)
    {
      return *this = Array(other);
    }

    // Standardna implementacija
    // Array& operator=(Array&& other)
    // {
    //   if (this != &other)
    //   {
    //     size_ = other.size_;
    //     capacity_ = other.capacity_;
    //
    //     delete[] data_;
    //
    //     data_ = other.data_;
    //
    //     other.size_ = other.capacity_ = 0;
    //     other.data_ = nullptr;
    //   }
    //
    //   return *this;
    // }

    // Alternativna implementacija
    Array& operator=(Array&& other)
    {
      std::swap(size_, other.size_);
      std::swap(capacity_, other.capacity_);
      std::swap(data_, other.data_);
      return *this;
    }

    ~Array()
    {
      delete[] data_;
    }

    void push_back(const T& element);
    void push_back(T&& element);

    T& operator[](size_t index)
    {
      return data_[index];
    }

    const T& operator[](size_t index) const
    {
      return data_[index];
    }

    T& at(size_t index)
    {
      if (index >= size_)
      {
        throw std::out_of_range { "Nevalidan indeks!" };
      }
      return data_[index];
    }

    const T& at(size_t index) const
    {
      if (index >= size_)
      {
        throw std::out_of_range { "Nevalidan indeks!" };
      }
      return data_[index];
    }

    T& front()
    {
      return data_[0];
    }
    const T& front() const
    {
      return data_[0];
    }
    T& back()
    {
      return data_[size_ - 1];
    }
    const T& back() const
    {
      return data_[size_ - 1];
    }

    void pop_back()
    {
      auto temp = std::move(data_[size_ - 1]);
      --size_;
    }

    void clear()
    {
      delete[] data_;
      size_ = 0;
      data_ = new T[capacity_];
    }

    bool empty() const
    {
      return size_ == 0;
    }
    size_t size() const
    {
      return size_;
    }

    class Iterator;

    Iterator begin()
    {
      return Iterator { data_ };
    }
    Iterator end()
    {
      return Iterator { data_ + size_ };
    }

  private:
    void reallocate();
    std::size_t capacity_;
    T* data_;
    std::size_t size_;
};

template <typename T>
void Array<T>::push_back(const T& element)
{
  std::cout << "copy push_back" << std::endl;
  if (size_ == capacity_)
    throw std::out_of_range("Nedostatak kapaciteta");

  data_[size_++] = element;
}

template <typename T>
void Array<T>::push_back(T&& element)
{
  std::cout << "move push_back" << std::endl;
  if (size_ == capacity_)
    throw std::out_of_range("Nedostatak kapaciteta");
  data_[size_++] = std::move(element);
}

// Vrste operatora
//
// forward
//  ++, *, ->, ==, !=
// bidirekcioni
//  --
// random access
//  + n, - n, >, <

template <typename T>
class Array<T>::Iterator
// : public std::iterator<std::random_access_iterator_tag, T> // ili ovo ili ovih 5 using-a, ali ne oba
{
  public:
    using iterator_category = std::random_access_iterator_tag;
    using value_type = T;
    using pointer = T*;
    using reference = T&;
    using difference_type = size_t;

    Iterator(T* p) : ptr_ { p } { }

    Iterator& operator++()
    {
      ++ptr_;
      return *this;
    }

    Iterator operator++(int)
    {
      return Iterator { ptr_++ };

      // auto temp = *this;
      // ++ptr_;
      // return temp;
    }

    Iterator& operator--()
    {
      --ptr_;
      return *this;
    }

    Iterator operator--(int)
    {
      return Iterator { ptr_-- };
    }

    bool operator!=(const Iterator& rhs) const
    {
      return this->ptr_ != rhs.ptr_;
    }

    bool operator==(const Iterator& rhs) const
    {
      return this->ptr_ == rhs.ptr_;
    }

    T& operator*()
    {
      return *this->ptr_;
    }

    T* operator->()
    {
      return this->ptr_;
    }

    long int operator-(const Iterator& rhs) const
    {
      return this->ptr_ - rhs.ptr_s;
    }

    Iterator operator+(int n) const
    {
      return Iterator { this->ptr_ + n };
    }

    Iterator
    operator-(int n) const
    {
      return Iterator { this->ptr_ - n };
    }

    bool operator<(const Iterator& rhs) const
    {
      return this->ptr_ < rhs.ptr_;
    }

  private:
    T* ptr_;
};
