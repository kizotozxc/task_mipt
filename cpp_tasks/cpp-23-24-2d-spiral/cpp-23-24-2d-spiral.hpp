int** MakeSpiral(int n) {
  const unsigned kSize = static_cast<unsigned>(n);
  int** spiral = new int*[kSize];
  for (unsigned i = 0; i < kSize; ++i) {
    spiral[i] = new int[kSize];
  }
  unsigned hight = 0;
  unsigned width = 0;
  unsigned num = 1;
  while (num <= kSize * kSize) {
    for (unsigned i = width; i < kSize - width; ++i) {
      spiral[width][i] = num;
      ++num;
    }
    ++width;
    for (unsigned i = hight + 1; i < kSize - hight; ++i) {
      spiral[i][kSize - hight - 1] = num;
      ++num;
    }
    ++hight;
    for (unsigned i = kSize - width - 1; i >= width; --i) {
      spiral[kSize - width][i] = num;
      ++num;
    }
    for (unsigned i = kSize - hight; i >= hight; --i) {
      spiral[i][hight - 1] = num;
      ++num;
    }
  }
  return spiral;
}