#include <Eigen/Dense>
#include <random>

void argsort(Eigen::MatrixXd& input_matrix, int32_t col_num, std::vector<int32_t>& output) {
  std::iota(output.begin(), output.end(), 0);
  auto comp_op = [&](size_t const &l, size_t const &r) { return std::less<double>{}(input_matrix(l, col_num), input_matrix(r, col_num)); };
  std::stable_sort(output.begin(), output.end(), comp_op);
}

int main() {
  // Random Number Generator
  std::random_device rd;
  std::mt19937 gen(rd());
  std::uniform_real_distribution<double> uniform_dist(0.,1.);

  // Initialize Eigen matrix
  int32_t n = 1000000;
  int32_t p = 10;
  Eigen::MatrixXd mat(n, p);
  
  // Generate data
  for (int32_t i = 0; i < n; i++) {
    for (int32_t j = 0; j < p; j++) {
      mat(i,j) = uniform_dist(gen);
    }
  }

  // Initialize a vector-of-vectors of sort indices for each column
  std::vector<std::vector<int32_t>> sort_indices(p);
  for (int32_t i = 0; i < p; i++) {
    sort_indices.at(i).resize(n,0);
    argsort(mat, i, sort_indices.at(i));
  }
}
