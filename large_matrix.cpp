#include <Eigen/Dense>
#include <numeric>
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
  std::normal_distribution<double> norm_dist(0.,1.);

  // Initialize Eigen matrix and vector
  int32_t n = 1000000;
  int32_t p = 100;
  Eigen::MatrixXd mat(n, p);
  Eigen::VectorXd vec(n);
  
  // Generate data
  for (int32_t i = 0; i < n; i++) {
    for (int32_t j = 0; j < p; j++) {
      mat(i,j) = uniform_dist(gen);
    }
    vec(i) = mat(i,0) * 2 + norm_dist(gen);
  }

  // Initialize a vector-of-vectors of sort indices for each column
  std::vector<std::vector<int32_t>> sort_indices(p);
  for (int32_t i = 0; i < p; i++) {
    sort_indices.at(i).resize(n,0);
    argsort(mat, i, sort_indices.at(i));
  }

  // Accumulate summary statistics for every possible partition of the data
  double sum_vec = 0;
  for (int32_t i = 0; i < n; i++) {
    sum_vec += vec(i);
  }
  std::vector<double> partition_ssqs(p*(n-1));
  double left_sum_vec;
  double right_sum_vec;
  double left_count;
  double right_count;
  int32_t offset;
  for (int32_t j = 0; j < p; j++) {
    left_sum_vec = 0;
    left_count = 0;
    for (int32_t i = 0; i < n-1; i++) {
      offset = sort_indices.at(j).at(i);
      left_sum_vec += vec(offset);
      left_count += 1.;
      right_sum_vec = sum_vec - left_sum_vec;
      right_count = n - left_count;
      partition_ssqs.at(j*(n-1) + i) = ((left_sum_vec*left_sum_vec)/left_count) + ((right_sum_vec*right_sum_vec)/right_count);
    }
  }
}
