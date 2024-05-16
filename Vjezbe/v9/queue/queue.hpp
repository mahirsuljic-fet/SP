#pragma once

#include <algorithm>
#include <list>
#include <stdexcept>
#include <utility>

template <typename T>
class Queue
{
  public:
    // ne treba pravilo petorke
    //
    // Queue() = default;
    // Queue(const Queue& other) = default;
    // Queue(Queue&& other) = default;
    // Queue& operator=(const Queue& other) = default;
    // Queue& operator=(Queue&& other) = default;
    // ~Queue() = default;

    void clear()
    {
      impl.clear();
    }

    size_t size() const
    {
      return impl.size();
    }

    bool empty() const
    {
      return impl.empty();
    }

    template <typename U>
    void push(U&& element)
    {
      impl.push_front(std::forward<U>(element));
    }

    // void push(const T& element)
    // {
    //   impl.push_front(element);
    // }
    //
    // void push(T&& element)
    // {
    //   impl.push_front(std::move(element));
    // }

    T pop()
    {
      auto temp = impl.back();
      impl.pop_back();
      return temp;
    }

    // void pop()
    // {
    //   impl.pop_back();
    // }

    const T& top() const
    {
      if (impl.empty()) throw std::runtime_error("Queue je prazan");
      return impl.back();
    }

    T& top()
    {
      if (impl.empty()) throw std::runtime_error("Queue je prazan");
      return impl.back();
    }

  private:
    std::list<T> impl;
};
