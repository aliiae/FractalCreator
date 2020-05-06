#include <Fractal.h>
#include <utils.h>

int Fractal::getMaxIterations() const { return max_iterations_; }
int Fractal::getIterations(std::complex<double> C) {
  std::complex<double> Z = C;
  std::complex<double> OrbitReference = Z;
  int OrbitCounter = 16;
  for (int Iteration = 0; Iteration < max_iterations_; ++Iteration) {
    if (abs(Z) >= 2.0) {
      return Iteration;
    }
    Z = calculateRecurrence(Z, C);
    if (OrbitReference == Z) {
      return max_iterations_;
    }
    if (OrbitCounter == Iteration) {
      OrbitReference = Z;
      OrbitCounter += 8;
    }
  }
  return max_iterations_;
}

/**
 * Formats the area as (left, right, top, bottom) coordinates to display to the
 * user.
 */
std::string Fractal::getZoomAreaString() {
  Area<double> A = getArea();
  return "(" + utils::formatDouble(A.getXMin()) + "," +
         utils::formatDouble(A.getXMax()) + "," +
         utils::formatDouble(A.getYMin()) + "," +
         utils::formatDouble(A.getYMax()) + ")";
}

Fractal::Fractal(int MaxIterations) : max_iterations_(MaxIterations) {}