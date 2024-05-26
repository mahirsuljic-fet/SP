#pragma once

#include <algorithm>
#include <stdexcept>
#include <utility>

template <typename T>
class Queue
{
  public:
    Queue();
    Queue(const Queue&);
    Queue(Queue&&);
    Queue& operator=(const Queue&);
    Queue& operator=(Queue&&);
    ~Queue();
    template <typename U>
    Queue& push(U&&);
    T pop();
    T& front();
    size_t size() const { return size_; }
    size_t capacity() const { return capacity_; }
    bool empty() const { return size_ == 0; }
    bool full() const { return size_ == capacity_; }
    void clear();

  private:
    size_t capacity_ { 0 };
    size_t size_ { 0 };
    T* arr_ { nullptr };
    size_t back_ { 0 };
    size_t front_ { 0 };
};

template <typename T>
Queue<T>::Queue() : capacity_ { 10 }, size_ { 0 }, arr_ { new T[capacity_] }, back_ { 0 }, front_ { 0 } { }

template <typename T>
Queue<T>::Queue(const Queue& other)
  : capacity_ { other.capacity_ }, size_ { other.size_ }, arr_ { new T[capacity_] }, back_ { other.back_ }, front_ { other.front_ }
{
  std::copy(other.arr_, other.arr_ + other.capacity_, this->arr_);
}

template <typename T>
Queue<T>::Queue(Queue&& other)
  : capacity_ { other.capacity_ }, size_ { other.size_ }, arr_ { new T[capacity_] }, back_ { other.back_ }, front_ { other.front_ }
{
  std::move(other.arr_, other.arr_ + other.capacity_, this->arr_);
  other.clear();
}

template <typename T>
Queue<T>& Queue<T>::operator=(const Queue& other)
{
  if (this != &other)
  {
    this->capacity_ = other.capacity_;
    this->size_ = other.size_;

    delete[] this->arr_;
    this->arr_ = new T[this->size_];
    std::copy(other.arr_, other.arr_ + other.size_, this->arr_);

    this->front_ = other.front_;
    this->back_ = other.back_;
  }
  return *this;
}

template <typename T>
Queue<T>& Queue<T>::operator=(Queue&& other)
{
  if (this != &other)
  {
    this->capacity_ = other.capacity_;
    this->size_ = other.size_;

    delete[] this->arr_;
    this->arr_ = new T[this->size_];
    std::move(other.arr_, other.arr_ + other.size_, this->arr_);

    this->front_ = other.front_;
    this->back_ = other.back_;

    other.clear();
  }
  return *this;
}

template <typename T>
Queue<T>::~Queue()
{
  clear();
}

template <typename T>
template <typename U>
Queue<T>& Queue<T>::push(U&& value)
{
  if (this->full()) throw std::out_of_range("Red je pun.");

  if (back_ == capacity_) back_ = 0;
  arr_[back_++] = std::forward<U>(value);
  ++size_;

  return *this;
}

template <typename T>
T Queue<T>::pop()
{
  if (this->empty()) throw std::out_of_range("Red je prazan.");

  T temp = arr_[front_++];
  if (front_ == capacity_) front_ = 0;
  --size_;

  return temp;
}

template <typename T>
T& Queue<T>::front()
{
  if (this->empty()) throw std::out_of_range("Red je prazan.");
  return arr_[front_];
}

template <typename T>
void Queue<T>::clear()
{
  delete[] arr_;
  arr_ = nullptr;
  size_ = 0;
  front_ = 0;
  back_ = 0;
}
