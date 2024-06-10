#pragma once

#include <algorithm>
#include <cstddef>
#include <initializer_list>
#include <iostream>
#include <ostream>
#include <stdexcept>
#include <utility>
#include <vector>

template <typename T>
class Heap
{
  public:
    Heap() = default;
    Heap(const std::initializer_list<T>&);
    Heap(Heap&&);
    Heap(const Heap&);
    ~Heap() = default;

    Heap& operator=(Heap&&);
    Heap& operator=(const Heap&);
    Heap& operator=(const std::initializer_list<T>& list);

    // T& max() { return tree_.front(); } // izbaceno jer bi bilo moguce poremetit osobinu heap-a
    const T& max() const { return tree_.front(); }
    Heap& push(const T&);
    Heap& push(T&&);
    Heap& clear();
    T removeMax();
    size_t size() const { return tree_.size(); }

    template <typename U>
    friend std::ostream& operator<<(std::ostream&, const Heap<U>&);

  private:
    std::vector<T> tree_;

    std::ostream& print_tree(int index, std::ostream& out = std::cout) const;
};

template <typename T>
Heap<T>::Heap(const std::initializer_list<T>& list)
{
  tree_.reserve(list.size());
  for (const auto& el : list)
    push(el);
}

template <typename T>
Heap<T>::Heap(Heap&& other) : tree_(std::move(other.tree_)) { }

template <typename T>
Heap<T>::Heap(const Heap& other) : tree_(other.tree_) { }

template <typename T>
Heap<T>& Heap<T>::operator=(Heap&& other)
{
  if (this != &other)
    this->tree_ = std::move(other.tree_);
  return *this;
}

template <typename T>
Heap<T>& Heap<T>::operator=(const Heap& other)
{
  this->tree_ = other.tree_;
  return *this;
}

template <typename T>
Heap<T>& Heap<T>::operator=(const std::initializer_list<T>& list)
{
  return *this = Heap(list);
}

template <typename T>
Heap<T>& Heap<T>::push(const T& value)
{
  int index = tree_.size();
  tree_.push_back(value);

  while (tree_[index] > tree_[index / 2])
  {
    std::swap(tree_[index], tree_[index / 2]);
    index >>= 1; // index /= 2;
  }

  return *this;
}

template <typename T>
Heap<T>& Heap<T>::push(T&& value)
{
  int index = tree_.size();
  tree_.push_back(std::move(value));

  while (tree_[index] > tree_[index / 2])
  {
    std::swap(tree_[index], tree_[index / 2]);
    index >>= 1; // index /= 2;
  }

  return *this;
}

template <typename T>
Heap<T>& Heap<T>::clear()
{
  tree_.clear();
}

template <typename T>
T Heap<T>::removeMax()
{
  if (tree_.empty()) throw std::runtime_error("Heap je prazan");

  T value = tree_.front();

  std::swap(tree_.front(), tree_.back());
  tree_.pop_back();

  int left_index;
  int right_index;
  int largest_index;
  int current_index = 0;

  while (current_index < tree_.size())
  {
    left_index = current_index * 2 + 1;
    right_index = current_index * 2 + 2;

    largest_index = left_index;

    // ako nema lijevog dijeta, cvor nema djece
    if (left_index >= tree_.size()) break;

    // provjeri da li cvor ima desno dijete i da li je ono najvece
    if (right_index < tree_.size() && tree_[right_index] > tree_[left_index]) largest_index = right_index;

    if (tree_[largest_index] > tree_[current_index])
      std::swap(tree_[current_index], tree_[largest_index]);
    else
      break;

    current_index = largest_index;
  }

  return value;
}

template <typename T>
std::ostream& operator<<(std::ostream& out, const Heap<T>& heap)
{
  return heap.print_tree(0, out);
}

template <typename T>
std::ostream& Heap<T>::print_tree(int index, std::ostream& out) const
{
  if (index < tree_.size())
  {
    out << tree_[index] << " ";
    print_tree(index * 2 + 1, out);
    print_tree(index * 2 + 2, out);
  }
  return out;
}
