#include "cpp-23-24-string.hpp"

#include <cstring>
#include <iostream>
#include <vector>

void String::ChangeMem(size_t new_size) {
  if (capacity_ == 0) {
    ++capacity_;
  }
  while (capacity_ < new_size) {
    capacity_ *= 2;
  }
  char* tmp = new char[capacity_ + 1];
  memcpy(tmp, buffer_, size_);
  delete[] buffer_;
  buffer_ = tmp;
  buffer_[capacity_] = '\0';
}

void String::ChangeMem() {
  char* tmp = new char[capacity_ + 1];
  memcpy(tmp, buffer_, std::min(size_, capacity_));
  delete[] buffer_;
  buffer_ = tmp;
  buffer_[capacity_] = '\0';
}

String::String(size_t size, char character)
    : size_(size), capacity_(size), buffer_(new char[size + 1]) {
  for (size_t i = 0; i < size; ++i) {
    buffer_[i] = character;
  }
  buffer_[size] = '\0';
}

String::String(const char* str) {
  size_t size = std::strlen(str);
  size_ = size;
  capacity_ = size;
  buffer_ = new char[size + 1];
  memcpy(buffer_, str, size);
  buffer_[size] = '\0';
}

String::String(const String& s) {
  size_ = s.size_;
  capacity_ = s.capacity_;
  buffer_ = new char[capacity_ + 1];
  memcpy(buffer_, s.buffer_, size_);
  buffer_[size_] = '\0';
}

String::~String() { delete[] buffer_; }

String& String::operator=(const String& s) {
  if (this == &s) {
    return *this;
  }
  size_ = s.size_;
  capacity_ = s.capacity_;
  delete[] buffer_;
  buffer_ = new char[capacity_ + 1];
  memcpy(buffer_, s.buffer_, size_ + 1);
  return *this;
}

void String::Clear() { size_ = 0; }

void String::PushBack(char character) {
  if (size_ == capacity_) {
    ChangeMem(size_ + 1);
  }
  ++size_;
  buffer_[size_ - 1] = character;
  buffer_[size_] = '\0';
}

void String::PopBack() {
  if (size_ != 0) {
    --size_;
    buffer_[size_] = '\0';
  }
}

void String::Resize(size_t new_size) {
  capacity_ = new_size;
  ChangeMem();
  size_ = new_size;
}

void String::Resize(size_t new_size, char character) {
  capacity_ = new_size;
  ChangeMem();
  for (; size_ < new_size; ++size_) {
    buffer_[size_] = character;
  }
}

void String::Reserve(size_t new_cap) {
  if (new_cap > capacity_) {
    capacity_ = new_cap;
    ChangeMem();
  }
}

void String::ShrinkToFit() {
  if (capacity_ > size_) {
    capacity_ = size_;
    ChangeMem();
  }
}

void String::Swap(String& s) {
  std::swap(capacity_, s.capacity_);
  std::swap(size_, s.size_);
  std::swap(buffer_, s.buffer_);
}

char& String::operator[](size_t index) { return buffer_[index]; }

const char& String::operator[](size_t index) const { return buffer_[index]; }

char& String::Front() { return buffer_[0]; }

const char& String::Front() const { return buffer_[0]; }

const char& String::Back() const { return buffer_[size_ - 1]; }

char& String::Back() { return buffer_[size_ - 1]; }

bool String::Empty() { return (size_ == 0); }

size_t String::Size() const { return size_; }

size_t String::Capacity() const { return capacity_; }

const char* String::Data() const { return buffer_; }

bool operator>(const String& s1, const String& s2) {
  const size_t kMinLen = (s1.Size() < s2.Size()) ? s1.Size() : s2.Size();
  for (size_t i = 0; i < kMinLen; ++i) {
    if (s1[i] != s2[i]) {
      return s1[i] > s2[i];
    }
  }
  return s1.Size() > s2.Size();
}

bool operator==(const String& s1, const String& s2) {
  if (s1.Size() != s2.Size()) {
    return false;
  }
  for (size_t i = 0; i < s1.Size(); ++i) {
    if (s1[i] != s2[i]) {
      return false;
    }
  }
  return true;
}

bool operator<(const String& s1, const String& s2) { return (s2 > s1); }

bool operator<=(const String& s1, const String& s2) { return !(s1 > s2); }

bool operator>=(const String& s1, const String& s2) { return !(s1 < s2); }

bool operator!=(const String& s1, const String& s2) { return !(s1 == s2); }

String operator+(const String& s1, const String& s2) {
  String str(s1);
  str += s2;
  return str;
}

String& String::operator+=(const String& s) {
  size_t size2 = s.size_;
  size_t size1 = size_;
  Resize(size1 + size2);
  for (size_t i = size1; i < size2 + size1; i++) {
    buffer_[i] = s.buffer_[i - size1];
  }
  return *this;
}

String operator*(const String& s, size_t times) {
  String str(s);
  str *= times;
  return str;
}

String String::operator*=(size_t times) {
  size_t size = Size();
  Resize(Size() * times);
  for (size_t i = 0; i < size; ++i) {
    for (size_t j = i; j < size * times; j += size) {
      buffer_[j] = buffer_[i];
    }
  }
  return *this;
}

std::ostream& operator<<(std::ostream& out, const String& str) {
  out << str.Data();
  return out;
}

std::istream& operator>>(std::istream& inp, String& str) {
  str.Clear();
  char elem;
  elem = inp.get();
  while (elem != ' ' && elem != '\n' && !inp.eof()) {
    str.PushBack(elem);
    elem = inp.get();
  }
  return inp;
}

std::vector<String> String::Split(const String& delim) {
  size_t head = 0;
  size_t size = delim.size_;
  std::vector<String> str;
  for (size_t i = 0, lenght = 0; i < size_; ++i) {
    if (buffer_[i] == delim.buffer_[lenght]) {
      ++lenght;
    } else {
      lenght = 0;
    }
    if (lenght == size) {
      String tmp;
      for (size_t k = head; k < i - size + 1; ++k) {
        tmp.PushBack(buffer_[k]);
      }
      str.push_back(tmp);
      head = i + 1;
      lenght = 0;
    }
  }
  String tmp;
  for (size_t k = head; k < size_; ++k) {
    tmp.PushBack(buffer_[k]);
  }
  str.push_back(tmp);
  return str;
}

String String::Join(const std::vector<String>& strings) {
  String str;
  size_t size = strings.size();
  if (size > 0) {
    str = strings[0];
    for (size_t i = 1; i < size; ++i) {
      str += *this;
      str += strings[i];
    }
  }
  return str;
}