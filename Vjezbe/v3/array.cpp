#include "array.h"
#include <algorithm>
#include <stdexcept>

Array::Array(const Array& other)
  : size_ { other.size_ },
    capacity_ { other.capacity_ },
    data_ { new int[capacity_] }
{
  std::copy(other.data_, other.data_ + size_, data_);
}

Array::Array(Array&& other)
  : size_ { other.size_ },
    capacity_ { other.capacity_ },
    data_ { new int[capacity_] }
{
  std::copy(other.data_, other.data_ + size_, data_);
  delete[] other.data_;

  other.size_ = 0;
  other.capacity_ = 1;
  other.data_ = nullptr;
}

Array& Array::operator=(const Array& other)
{
  if (data_ != other.data_)
  {
    size_ = other.size_;
    capacity_ = other.capacity_;
    data_ = new int[capacity_];

    std::copy(other.data_, other.data_ + size_, data_);
  }

  return *this;
}

Array& Array::operator=(Array&& other)
{
  if (data_ != other.data_)
  {
    size_ = other.size_;
    capacity_ = other.capacity_;
    data_ = new int[capacity_];

    std::copy(other.data_, other.data_ + size_, data_);
    delete[] other.data_;

    other.size_ = 0;
    other.capacity_ = 1;
    other.data_ = nullptr;
  }

  return *this;
}

Array::~Array()
{
  delete[] data_;
}

void Array::push_back(const int& element)
{
  if (size_ < capacity_)
  {
    data_[size_++] = element;
  }
  else
  {
    // throw std::out_of_range("Nema vise prostora u nizu");

    int* old = data_;
    capacity_ *= 2;
    data_ = new int[capacity_];
    std::copy(old, old + size_, data_);
    data_[size_++] = element;
    delete[] old;
  }
}

int& Array::at(size_t index)
{
  if (index >= size_) // nema potrebe provjeravati da li je pozitivan jer je size_t unsigned
    throw std::out_of_range("Indeks je van granica");

  return data_[index];
}

const int& Array::at(size_t index) const
{
  if (index >= size_) throw std::out_of_range("Indeks je van granica");

  return data_[index];
}
