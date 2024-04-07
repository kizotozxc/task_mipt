#pragma once
#include <vector>

std::vector<int> Factorize(int n) {
  std::vector<int> dividers;
  unsigned i = 2;
  unsigned num = static_cast<unsigned>(n);
  while (i * i <= num) {
    if (num % i == 0) {
      dividers.push_back(i);
      num /= i;
    } else {
      ++i;
    }
  }
  if (num != 1) {
    dividers.push_back(num);
  }
  return dividers;
}