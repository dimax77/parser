#include <stdio.h>

#include <memory>
#include <vector>

int main() {
  size_t n = 10;
  auto matrix_data = std::make_unique<double[]>(n * n);
  auto matrix = std::make_unique<double*[]>(n);
  for (int i = 0; i < 10; i++) {
    matrix.get()[i] = matrix_data.get() + i * n;
  }
}

template <typename T>
class MyMatrix {
  // etc. etc
  std::vector << std::vector < double >>
      mat(10, std::vector<double>(10, nan("")));
  double const T& operator[](size_type i, size_type j) const {
    return data_[i * n + j];
  }
  double T& operator[](size_type i, size_type j) { return data_[i * n + j]; }
};
