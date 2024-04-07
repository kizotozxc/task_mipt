#pragma once

#include <cstddef>

class RingBuffer {
 public:
  explicit RingBuffer(size_t capacity)
      : capacity_(capacity), buffer_(new int[capacity]) {}

  size_t Size() const { return size_; }

  bool Empty() const { return size_ == 0; }

  bool TryPush(int element) {
    if (size_ == capacity_) {
      return false;
    }
    buffer_[tail_] = element;
    tail_ == capacity_ - 1 ? tail_ = 0 : ++tail_;
    ++size_;
    return true;
  }

  bool TryPop(int* element) {
    if (size_ == 0) {
      return false;
    }
    *element = buffer_[head_];
    head_ == capacity_ - 1 ? head_ = 0 : ++head_;
    --size_;
    return true;
  }

  ~RingBuffer() { delete[] buffer_; }

 private:
  size_t head_ = 0;
  size_t tail_ = 0;
  size_t capacity_;
  size_t size_ = 0;
  int* buffer_ = nullptr;
};