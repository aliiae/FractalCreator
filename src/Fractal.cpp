#include "Fractal.h"

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

std::string formatDouble(double Double) {
  std::stringstream Stream;
  Stream.setf(std::ios::fixed);
  Stream.precision(1);
  Stream << Double;
  return Stream.str();
}

std::string Fractal::getZoomAreaString() {
  Area<double> A = getArea();
  return "(" + formatDouble(A.getXMin()) + "," + formatDouble(A.getXMax()) +
         "," + formatDouble(A.getYMin()) + "," + formatDouble(A.getYMax()) +
         ")";
}

Fractal::Fractal(int MaxIterations) : max_iterations_(MaxIterations) {}