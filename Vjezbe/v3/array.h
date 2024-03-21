#pragma once

#include <algorithm>
#include <stdexcept>
#include <type_traits>

class Array
{
  public:
    Array() : size_(0), capacity_(100), data_(new int[capacity_]) { }
    Array(const std::size_t capacity) : size_(0), capacity_(capacity), data_(new int[capacity]) { }

    // kada se koristi konstruktor sa {} ne dozvoljava da se gube podaci
    // npr ne dozvoljava double u float, long u int, itd.

    Array(const Array& other);
    Array(Array&& other);

    Array& operator=(const Array& other);
    Array& operator=(Array&& other);

    ~Array();

    void push_back(const int& element);

    int& operator[](size_t index) { return data_[index]; }
    const int& operator[](size_t index) const { return data_[index]; }

    int& at(size_t index);
    const int& at(size_t index) const;

    bool empty() const { return size_ == 0; }
    size_t size() const { return size_; }

  private:
    std::size_t size_;
    std::size_t capacity_;
    int* data_;
};
