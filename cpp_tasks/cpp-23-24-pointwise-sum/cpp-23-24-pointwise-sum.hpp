int* PointwiseSum(const int* a, const int* b, int n) {
  int* sum = new int[n];
  for (unsigned i = 0; i < n; ++i) {
    sum[i] = a[i] + b[i];
  }
  return sum;
}