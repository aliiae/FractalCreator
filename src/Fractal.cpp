#include "Fractal.h"

[[maybe_unused]] void Fractal::zoom(const double WindowRatio,
                                    Area<double> NewArea) {
  NewArea.setYMax(NewArea.getYMin() + (NewArea.width() * WindowRatio));
  setZoomArea(NewArea);
}
void Fractal::setOrder(int Order) { order_ = Order; }
int Fractal::getOrder() const { return order_; }
int Fractal::getMaxIterations() const { return max_iterations_; }
int Fractal::getIterations(std::complex<double> C) {
  std::complex<double> Z = C;
  for (int Iteration = 0; Iteration < max_iterations_; ++Iteration) {
    Z = calculateRecurrence(Z, C);
    if (abs(Z) >= 2.0) {
      return Iteration;
    }
  }
  return max_iterations_;
}
