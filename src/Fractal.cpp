#include "Fractal.h"

int Fractal::getMaxIterations() const { return max_iterations_; }
std::complex<double>
MandelbrotSet::calculateRecurrence(std::complex<double> Z,
                                   std::complex<double> C) {
  return Z * Z + C;
}
Area<double> MandelbrotSet::getArea() { return zoom_area_; }
void MandelbrotSet::setArea(Area<double> &FractalArea) {
  zoom_area_ = FractalArea;
}
std::string MandelbrotSet::getName() { return name_; }
std::complex<double> BurningShip::calculateRecurrence(std::complex<double> Z,
                                                      std::complex<double> C) {
  Z = abs(Z.real()) + ImaginaryOne * abs(Z.imag());
  return Z * Z + C;
}
Area<double> BurningShip::getArea() { return zoom_area_; }
void BurningShip::setArea(Area<double> &FractalArea) {
  zoom_area_ = FractalArea;
}
std::string BurningShip::getName() { return name_; }
const std::complex<double> &BurningShip::ImaginaryOne{0, 1.0};

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
Fractal::Fractal(int MaxIterations) : max_iterations_(MaxIterations) {}