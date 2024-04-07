#pragma once
#include <iostream>
#include <vector>

class String {
 public:
  String() = default;
  String(size_t size, char character);
  String(const char* str);
  String(const String& s);
  ~String();
  String& operator=(const String& s);
  void Clear();
  void PushBack(char character);
  void PopBack();
  void Resize(size_t new_size);
  void Resize(size_t new_size, char character);
  void Reserve(size_t new_cap);
  void ShrinkToFit();
  void Swap(String& s);
  char& operator[](size_t index);
  const char& operator[](size_t index) const;
  char& Front();
  const char& Front() const;
  char& Back();
  const char& Back() const;
  bool Empty();
  size_t Size() const;
  size_t Capacity() const;
  const char* Data() const;
  String& operator+=(const String& s);
  String operator*=(size_t times);
  std::vector<String> Split(const String& delim = " ");
  String Join(const std::vector<String>& strings);

 private:
  size_t size_ = 0;
  size_t capacity_ = 0;
  char* buffer_ = nullptr;
  void ChangeMem(size_t new_size);
  void ChangeMem();
};

bool operator>(const String& s1, const String& s2);
bool operator<(const String& s1, const String& s2);
bool operator<=(const String& s1, const String& s2);
bool operator>=(const String& s1, const String& s2);
bool operator==(const String& s1, const String& s2);
bool operator!=(const String& s1, const String& s2);
String operator+(const String& s1, const String& s2);
String operator*(const String& s, size_t times);
std::ostream& operator<<(std::ostream& out, const String& str);
std::istream& operator>>(std::istream& inp, String& str);
