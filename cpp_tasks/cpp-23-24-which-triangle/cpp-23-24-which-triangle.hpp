#pragma once

#include <algorithm>

void Sort(int& a, int& b, int& c) {
  if (b > a) {
    std::swap(b, a);
  }
  if (c > b) {
    std::swap(b, c);
  }
  if (b > a) {
    std::swap(a, b);
  }
}
int WhichTriangle(int a, int b, int c) {
  Sort(a, b, c);
  if (a > b + c) {
    return 0;
  }
  if (a == c + b) {
    return 1;
  }
  const long long kCos =
      (static_cast<long long>(c) * c + static_cast<long long>(b) * b -
       static_cast<long long>(a) * a);
  if (kCos > 0) {
    return 2;
  }
  if (kCos == 0) {
    return 3;
  }
  return 4;
}