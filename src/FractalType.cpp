#include "FractalType.h"

void FractalType::zoom(const double WindowRatio, Area<double> NewArea) {
  NewArea.setYMax(NewArea.getYMin() + (NewArea.width() * WindowRatio));
  setFractalArea(NewArea);
}

std::complex<double>
MandelbrotSet::calculateRecurrence(std::complex<double> Z,
                                   std::complex<double> C) {
  // Works faster than std::pow
  for (int Power = 1; Power < order_; Power++) {
    Z *= Z;
  }
  return Z + C;
}
Area<double> MandelbrotSet::getFractalArea() { return fractal_area_; }
void MandelbrotSet::setFractalArea(Area<double> &FractalArea) {
  fractal_area_ = FractalArea;
}
FractalName MandelbrotSet::getName() { return MANDELBROT_SET; }
std::complex<double> BurningShip::calculateRecurrence(std::complex<double> Z,
                                                      std::complex<double> C) {
  Z = abs(Z.real()) + ImaginaryOne * abs(Z.imag());
  for (int Power = 1; Power < order_; Power++) {
    Z *= abs(Z.real()) + ImaginaryOne * abs(Z.imag());
  }
  return Z + C;
}
Area<double> BurningShip::getFractalArea() { return fractal_area_; }
void BurningShip::setFractalArea(Area<double> &FractalArea) {
  fractal_area_ = FractalArea;
}
FractalName BurningShip::getName() { return BURNING_SHIP; }
const std::complex<double> &BurningShip::ImaginaryOne{0, 1.0};
