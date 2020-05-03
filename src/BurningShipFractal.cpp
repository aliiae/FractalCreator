#include "BurningShipFractal.h"

std::complex<double>
BurningShipFractal::calculateRecurrence(std::complex<double> Z,
                                        std::complex<double> C) {
  return std::complex<double>{
      abs(Z.real() * Z.real() - Z.imag() * Z.imag() + C.real()),
      abs(2 * Z.real() * Z.imag() + C.imag())};
}
Area<double> BurningShipFractal::getFractalArea() { return fractal_area_; }
void BurningShipFractal::setFractalArea(const Area<double> &FractalArea) {
  fractal_area_ = FractalArea;
}
