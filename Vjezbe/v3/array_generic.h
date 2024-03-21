#pragma once

#include <algorithm>
#include <stdexcept>
#include <type_traits>

template <typename T>
class Array
{
  public:
    Array() : size_(0), capacity_(100), data_(new T[capacity_]) { }
    Array(const std::size_t capacity) : size_(0), capacity_(capacity), data_(new T[capacity]) { }

    // kada se koristi konstruktor sa {} ne dozvoljava da se gube podaci
    // npr ne dozvoljava double u float, long u T, itd.

    Array(const Array& other);
    Array(Array&& other);

    Array& operator=(const Array& other);
    Array& operator=(Array&& other);

    ~Array();

    void push_back(const T& element);

    T& operator[](size_t index) { return data_[index]; }
    const T& operator[](size_t index) const { return data_[index]; }

    T& at(size_t index);
    const T& at(size_t index) const;

    bool empty() const { return size_ == 0; }
    size_t size() const { return size_; }

  private:
    std::size_t size_;
    std::size_t capacity_;
    T* data_;
};
