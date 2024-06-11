#pragma once

#include <cstddef>
#include <initializer_list>
#include <iostream>
#include <ostream>
#include <string>
#include <type_traits>
#include <utility>
#include <vector>

template <typename T>
class MinHeap
{
  public:
    MinHeap() = default;
    MinHeap(const std::initializer_list<T>&);
    template <typename F>
    MinHeap(MinHeap<F>&&);
    MinHeap& operator=(const std::initializer_list<T>&);
    template <typename F>
    MinHeap& operator=(MinHeap<F>&&);
    ~MinHeap();

    template <typename F>
    MinHeap& push(F&&);
    T pop_min();
    const T& min() const { return tree_.front(); }
    const size_t size() const { return tree_.size(); }
    void clear();

    template <typename U>
    friend std::ostream& operator<<(std::ostream&, const MinHeap<U>&);

  private:
    std::vector<T> tree_;

    std::ostream& print_node_(int index, std::ostream& out = std::cout) const;
};

template <typename T>
MinHeap<T>::MinHeap(const std::initializer_list<T>& list)
{
  tree_.reserve(list.size());
  for (const auto& el : list)
    push(el);
}

template <typename T>
template <typename F>
MinHeap<T>::MinHeap(MinHeap<F>&& other)
  : tree_ { std::forward<decltype(other.tree_)>(other.tree_) } { }

template <typename T>
MinHeap<T>::~MinHeap()
{
  clear();
}

template <typename T>
MinHeap<T>& MinHeap<T>::operator=(const std::initializer_list<T>& list)
{
  clear();
  return *this = MinHeap { list };
}

template <typename T>
template <typename F>
MinHeap<T>& MinHeap<T>::operator=(MinHeap<F>&& other)
{
  this->clear();
  this->tree_ = std::forward<decltype(other.tree_)>(other.tree_);
  return *this;
}

template <typename T>
template <typename F>
MinHeap<T>& MinHeap<T>::push(F&& value)
{
  int previous_index;
  int current_index = tree_.size();

  tree_.push_back(std::forward<F>(value));

  while (current_index > 0)
  {
    previous_index = current_index;
    current_index >>= 1;

    if (tree_[previous_index] < tree_[current_index])
      std::swap(tree_[previous_index], tree_[current_index]);
  }

  return *this;
}

template <typename T>
T MinHeap<T>::pop_min()
{
  T min = tree_.front();

  if (tree_.size() == 1)
  {
    tree_.pop_back();
    return min;
  }

  std::swap(tree_.front(), tree_.back());
  tree_.pop_back();

  int parent_index = 0;
  int left_index = (parent_index << 1) + 1;
  int right_index = (parent_index << 1) + 2;

  while (right_index < tree_.size())
  {
    int min_child_index = tree_[left_index] < tree_[right_index] ? left_index : right_index;

    if (tree_[min_child_index] < tree_[parent_index])
    {
      std::swap(tree_[min_child_index], tree_[parent_index]);
      parent_index = min_child_index;
    }
    else
      break;

    left_index = (parent_index << 1) + 1;
    right_index = (parent_index << 1) + 2;
  }

  if (tree_.size() > 1)
    if (tree_[1] < tree_[0])
      std::swap(tree_[1], tree_[0]);

  return min;
}

template <typename T>
void MinHeap<T>::clear()
{
  tree_.clear();
}

template <typename T>
std::ostream& operator<<(std::ostream& out, const MinHeap<T>& heap)
{
  return heap.print_node_(0, out);
}

template <typename T>
std::ostream& MinHeap<T>::print_node_(int index, std::ostream& out) const
{
  if (index < this->size())
  {
    out << tree_[index] << " ";
    print_node_((index << 1) + 1, out);
    print_node_((index << 1) + 2, out);
  }
  return out;
}
