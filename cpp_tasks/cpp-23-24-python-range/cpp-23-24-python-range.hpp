#include <utility>

std::pair<int, const int*> Range(int from, int to, int step = 1) {
  if (from == to || step == 0 || (to - from) / step < 0) {
    return std::pair<int, const int*>(0, nullptr);
  }
  const unsigned kNum = (to - from + (step / 2)) / (step);
  int* range = new int[kNum];
  for (unsigned i = 0; i < kNum; ++i) {
    range[i] = from + i * step;
  }
  return std::pair<int, const int*>(kNum, range);
}
