#pragma once

#include <stdexcept>
#include <vector>

template <typename T>
class Queue {
public:
  Queue() = default;
  Queue(const Queue& other);
  Queue(Queue&& other);
  Queue& operator=(const Queue& other);
  Queue& operator=(Queue&& other);
  ~Queue();

  void clear() {
    impl.clear();
  }

  size_t size() const {
    return impl.size();
  }

  bool empty() const {
    return impl.empty();
  }

  void push(const T& element) {
  }

  void push(const T&& element) {
  }

  void pop() {
  }

  const T& top() const {
  }

  T& top() {
  }

private:
  std::vector<T> impl;
};
