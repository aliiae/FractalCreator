#include "Fractal.h"

void Fractal::zoom(const double WindowRatio, Area<double> NewArea) {
  NewArea.setYMax(NewArea.getYMin() + (NewArea.width() * WindowRatio));
  setZoomArea(NewArea);
}
void Fractal::setOrder(int Order) { order_ = Order; }
int Fractal::getOrder() const { return order_; }
std::complex<double>
MandelbrotSet::calculateRecurrence(std::complex<double> Z,
                                   std::complex<double> C) {
  for (int Power = 1; Power < order_; Power++) {
    Z *= Z;
  }
  return Z + C;
}
Area<double> MandelbrotSet::getZoomArea() { return zoom_area_; }
void MandelbrotSet::setZoomArea(Area<double> &FractalArea) {
  zoom_area_ = FractalArea;
}
std::string MandelbrotSet::getName() { return name_; }
std::complex<double> BurningShip::calculateRecurrence(std::complex<double> Z,
                                                      std::complex<double> C) {
  Z = abs(Z.real()) + ImaginaryOne * abs(Z.imag());
  for (int Power = 1; Power < order_; Power++) {
    Z *= abs(Z.real()) + ImaginaryOne * abs(Z.imag());
  }
  return Z + C;
}
Area<double> BurningShip::getZoomArea() { return zoom_area_; }
void BurningShip::setZoomArea(Area<double> &FractalArea) {
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
