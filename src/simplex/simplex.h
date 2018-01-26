#pragma once

#include <cstdint>
#include <vector>

namespace geom {

template <typename T>
class Simplex {
  // TODO: Constraints on T -> need to define d dimensional point
  std::vector<T> points;

 public:
  Simplex(std::vector<T>&& p) : points(std::move(p)) {}

  void print() {
    std::cout << "Dimension: " << dimension() << "\nPoints: (" << points[0]
              << ", " << points[1] << ", " << points[2] << ")\n";
  }

  int32_t dimension() { return points.size(); }
};
}  // namespace geom
