#pragma once

#include <algorithm>
#include <forward_list>
#include <utility>

template <typename T>
class Stack
{
  public:
    Stack() = default;
    Stack(const Stack& other) = default;
    Stack(Stack&& other) = default;
    Stack& operator=(const Stack& other) = default;
    Stack& operator=(Stack&& other) = default;
    ~Stack() = default;

    bool empty() const
    {
      return impl.empty();
    }

    void clear()
    {
      return impl.clear();
    }

    T& top()
    {
      return impl.front();
    }

    const T& top() const
    {
      return impl.front();
    }

    T pop()
    {
      auto temp = impl.front();
      impl.pop_front();
      return temp;
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

  private:
    std::forward_list<T> impl;
};
