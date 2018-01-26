
#include <cstdint>
#include <iostream>
#include <vector>
#include <random>

#include <Eigen/Dense>

#include "simplex/simplex.h"

//using namespace Eigen;


// TODO(@dthg) make input vector of Eigen::Vector
float calculate_volume(std::vector<float> input, size_t dimension) {
  // TODO(@dthg) assert dims are correct;
  size_t n = dimension + 1;
  Eigen::Map<Eigen::MatrixXf> mat(input.data(), dimension, n);
  //std::cout << "matrix is: \n" << 3.0 * mat << "\n";

  Eigen::Map<Eigen::MatrixXf> slice(mat.data() + dimension, dimension, dimension);

  for(int i = 1; i < n; i++) {
    mat.col(i - 1) = 3 * mat.col(i) - 3 * mat.col(0);
  }

  //std::cout << "Slice is :\n" << slice << "\n";

  double det =  (slice / 1000).determinant();
  std::cout << "Determinant is: " << det << "\n";

  // can this be ignored as is constant factor
  // or will volume get too large as dim >>?
  double volume = det;
  for (auto i = n; i > 1; i--) {
    volume /= i;
    // std::cout << "Divide by: " << i << "\n";
    // std::cout << "Vol is: " << volume << "\n";
  }

  std::cout << "\nVolume is: " << 100 * volume << "\n";

  return volume;
}

std::vector<float> generate_simplex(size_t dim) {
  size_t num_elems = dim * (dim + 1);
  std::vector<float> data(num_elems);

  std::random_device rand_dev;
  std::mt19937_64 gen(rand_dev());
  std::normal_distribution<> dist{ 100/*mean*/, 5/*variance*/ };

  for (auto&& i: data) {
    i = dist(gen);
  }

  return data;
}

int main(int argc, char** argv) {
  //Matrix3f A;
  //A << 1, 2, 1, 2, 1, 0, -1, 1, 2;
  //std::cout << "Here is the matrix A:\n" << A << "\n";
  //std::cout << "The determinant of A is " << A.determinant() << "\n";
  //std::cout << "The inverse of8A is:\n" << A.inverse() << "\n";
  int dimension = 2;
  if (argc == 2) {
    std::cout << argv[1] << "\n";
    dimension = std::stoi(argv[1]);
  } else {
    std::cout << "No dimension supplied. Defaulting to dimension == " << dimension << "\n";
  }

  std::cout << "Using dimension:  " << dimension << "\n";

 auto data(generate_simplex(dimension));
  //std::vector<float> data{
  //  0.0f, 1.0f, 2.0f, 
  //  3.0f, 4.0f, 5.0f,
  //  6.0f, 7.0f, 8.0f,
  //  9.9f, 10.0f, 11.0f
  // };

  auto mat = calculate_volume(data, dimension);
  // auto s = geom::Simplex<float>{std::move(data)};

  // s.print();
  // std::cout << "Hello World!\n";
}
